#include "ImageViewer.h"

namespace ImgProc
{
  void ImageViewer::start()
  {
    _loopStatus = true;
    _viewerThread = std::thread(&ImageViewer::loop, this);
  }

  void ImageViewer::stop()
  {
    _loopStatus = false;
    _viewerThread.join();

    if(! _viewerThread.joinable() )
    { }//log
  }

  int ImageViewer::addWindow(std::string name)
  {
    std::lock_guard<std::mutex> guard(_mu);

    _mapStatus = _windowMap.emplace(std::make_pair(name, std::make_unique<Window>(name)));
    
    if(! _mapStatus.second )
    { return ImageViewerCodes::UnableToPlaceWindow; }

    cv::namedWindow(name);

    return NoError;
  }

  int ImageViewer::addWindow( const std::string& winName, 
                              const std::string& directory, 
                              const std::string& baseFileName, 
                              const std::string& extensionType )
  {
    std::lock_guard<std::mutex> guard(_mu);

    _mapStatus = _windowMap.emplace(std::make_pair(winName, std::make_unique<Window>(winName)));
    
    if(! _mapStatus.second )
    { return ImageViewerCodes::UnableToPlaceWindow; }

    cv::namedWindow(winName);

    _ptrFileHandler = std::make_shared< FileHandler >();
    _fhError = _ptrFileHandler->addPath( winName, directory, baseFileName, extensionType );

    if( _fhError )
    { return _fhError; }

    _mapStatus.first->second->ptrFileHandler = _ptrFileHandler;
    _mapStatus.first->second->iPath = _ptrFileHandler->getIterator( winName );
    
    return NoError;
  }

  int ImageViewer::setPath( const std::string& winName, 
                            const std::string& directory, 
                            const std::string& baseFileName, 
                            const std::string& extensionType )
  {
    std::lock_guard<std::mutex> guard(_mu);

    _iWindow = _windowMap.find(winName);
    
    if( _iWindow == _windowMap.end() )
    { return ImageViewerCodes::WindowDoesNotExist; }

    _ptrFileHandler = std::make_shared< FileHandler >();
    _fhError = _ptrFileHandler->addPath( winName, directory, baseFileName, extensionType );

    if( _fhError )
    { return _fhError; }

    _mapStatus.first->second->ptrFileHandler = _ptrFileHandler;
    _mapStatus.first->second->iPath = _ptrFileHandler->getIterator( winName );
    
    return NoError;
  }

  int ImageViewer::updateWindow(std::string name, cv::Mat& image)
  {
    _iWindow = _windowMap.find(name);
    if(_iWindow == _windowMap.end() )
    { return ImageViewerCodes::WindowDoesNotExist; }

    _iWindow->second->setImage(image);
    return NoError;
  }

  int ImageViewer::saveAllImages()
  {
    std::lock_guard<std::mutex> guard(_mu);
    _iWindow = _windowMap.begin();

    for(; _iWindow!=_windowMap.end(); _iWindow++)
    {
      _fhError = _iWindow->second->writeImage(); 
      break;
    }

    return _fhError;
  }

  bool ImageViewer::getStatus()
  {
    std::lock_guard<std::mutex> guard(_mu);
    return _loopStatus;
  }

  void ImageViewer::addTrackbarRGB(const std::string& name)
  {
    _iWindow = _windowMap.find(name);
    _iWindow->second->addTrackbar("bMin", &(_rgbArray[0]), 255); 
    _iWindow->second->addTrackbar("gMin", &(_rgbArray[1]), 255); 
    _iWindow->second->addTrackbar("rMin", &(_rgbArray[2]), 255); 
    _iWindow->second->addTrackbar("bMax", &(_rgbArray[3]), 255); 
    _iWindow->second->addTrackbar("gMax", &(_rgbArray[4]), 255); 
    _iWindow->second->addTrackbar("rMax", &(_rgbArray[5]), 255); 
  }

  void ImageViewer::getTrackbarRGBValues(std::array<int,6>& rgbArray)
  {
    rgbArray[0] = (uint8_t)_rgbArray[0];
    rgbArray[1] = (uint8_t)_rgbArray[1];
    rgbArray[2] = (uint8_t)_rgbArray[2];
    rgbArray[3] = (uint8_t)_rgbArray[3];
    rgbArray[4] = (uint8_t)_rgbArray[4];
    rgbArray[5] = (uint8_t)_rgbArray[5];
  }

  void ImageViewer::loop()
  {
    int key = 0;
    std::map<std::string, std::unique_ptr<Window>>::iterator iWindow = _windowMap.begin();
    while(_loopStatus)
    {
      iWindow = _windowMap.begin();
      for(; iWindow!=_windowMap.end(); iWindow++)
      {
        usleep(100);

        // If locked, will wait till unlocked
        if(! iWindow->second->mu.try_lock() )
        { continue; }

        // If empty, skip
        if(iWindow->second->image.empty() )
        { 
          iWindow->second->mu.unlock();
          continue; 
        }

        cv::imshow(iWindow->first, iWindow->second->image);
        
        // Wait for key press on window
        key = cv::waitKey(10);

        // x - close window
        if(key == 120 )
        { cv::destroyWindow(iWindow->first); }

        // s - save image 
        else if(key == 115)
        { 
          _fhError = iWindow->second->writeImage(); 
          std::cout << "ImageViewer::writeImage: " << _fhError << "\n";
        }

        // S - save all images
        else if(key == 83)
        { 
          _fhError = saveAllImages();
          std::cout << "ImageViewer::writeImage: " << _fhError << "\n";
        }

        // esc - close window
        if(key == 27 )
        {
          std::lock_guard<std::mutex> guard(_mu);
          _loopStatus = false; 
          cv::destroyAllWindows(); 
        }

        iWindow->second->mu.unlock();
      }
    }

    cv::destroyAllWindows();
    return;
  }
}
