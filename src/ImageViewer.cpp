#include "ImageViewer.h"

namespace ImgProc
{
  void ImageViewer::start()
  {
    _loopStatus = true;
    _viewerThread = std::thread(&ImageViewer::_loop, this);
  }

  void ImageViewer::stop()
  {
    _loopStatus = false;
    _viewerThread.join();

    if(! _viewerThread.joinable() )
    { }//log
  }

  int ImageViewer::addWindow( const std::string& winName)
  {
    std::lock_guard<std::mutex> guard(_mu);

    _mapStatus = _windowMap.emplace(std::make_pair(winName, std::make_unique<Window>(winName)));
    
    if(! _mapStatus.second )
    { return ImageViewerCodes::UnableToPlaceWindow; }

    _mapStatus.first->second->open();
    _mapStatus.first->second->enableVectWrite();

    return NoError;
  }

  int ImageViewer::addWindow( const std::string& winName, std::shared_ptr< File > pFile, bool enableVectWrite)
  {
    std::lock_guard<std::mutex> guard(_mu);

    _mapStatus = _windowMap.emplace(std::make_pair(winName, std::make_unique<Window>(winName)));
    
    if(! _mapStatus.second )
    { return ImageViewerCodes::UnableToPlaceWindow; }

    _mapStatus.first->second->open();
    _mapStatus.first->second->enableFileWrite(pFile);

    if( enableVectWrite )
    { _mapStatus.first->second->enableVectWrite(); }
    
    return NoError;
  }

  int ImageViewer::remove(const std::string& name)
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    _windowIter = _windowMap.find(name);
    if(_windowIter == _windowMap.end() )
    { return ImageViewerCodes::WindowDoesNotExist; }
    
    _windowIter->second->close();
    _windowMap.erase(name);

    return ImageViewerCodes::NoError;
  }

  int ImageViewer::updateWindow(std::string name, cv::Mat& image)
  {
    _windowIter = _windowMap.find(name);
    if(_windowIter == _windowMap.end() )
    { return ImageViewerCodes::WindowDoesNotExist; }

    _windowIter->second->setImage(image);
    return NoError;
  }

  bool ImageViewer::getStatus()
  {
    std::lock_guard<std::mutex> guard(_mu);
    return _loopStatus;
  }

  int ImageViewer::getSavedImages(const std::string& name, std::shared_ptr< std::vector< cv::Mat >> pVectMat)
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    _windowIter = _windowMap.find(name);
    if( _windowIter == _windowMap.end() )
    { return ImageViewerCodes::WindowDoesNotExist; }

    if(! _windowIter->second->vectWriteEnabled )
    { return ImageViewerCodes::NoError; }
      
    _windowIter->second->getVector(pVectMat);
    return ImageViewerCodes::NoError;
  }

  int ImageViewer::getNumSavedImages(const std::string& name)
  { 
    _windowIter = _windowMap.find(name);
    if(_windowIter == _windowMap.end() )
    { return ImageViewerCodes::WindowDoesNotExist; }

    return _windowIter->second->getNumSaved();
  }

  int ImageViewer::_saveAll()
  {
    windowIter iWin = _windowMap.begin();

    for(; iWin!=_windowMap.end(); iWin++)
    { 
      _fhError = iWin->second->write(); 
      if( _fhError )
      { return _fhError; }
    }

    return ImageViewerCodes::NoError;
  }

  void ImageViewer::_closeAll()
  {
    windowIter iWin = _windowMap.begin();

    for(; iWin!=_windowMap.end(); iWin++)
    { iWin->second->close(); }
  }

  void ImageViewer::_keyInterface( int key )
  {
    // ESC - close all windows and stop viewer
    if(key == 27)
    { 
      _closeAll();
      _loopStatus = false; 
    }

    // S - save all images
    else if(key == 83)
    { _fhError = _saveAll(); }

    // X - close all windows
    else if(key == 88 )
    { _closeAll(); }
  }

  void ImageViewer::_loop()
  {
    int key = 0;
    while(_loopStatus)
    {
      // Prevent adding / removing windows
      _mu.lock();

      // Loop through windows
      _loopIterBegin = _windowMap.begin();
      _loopIterEnd = _windowMap.end();
      for(; _loopIterBegin!=_loopIterEnd; _loopIterBegin++)
      {
        // Display image, do window specific operations
        _loopIterBegin->second->display( key );

        // Do key operations
        _keyInterface( key );
      }

      // Allow adding / removing windows
      _mu.unlock();
      usleep(100);
    }
    return;
  }

/*
  void ImageViewer::addTrackbarRGB(const std::string& name)
  {
    _windowIter = _windowMap.find(name);
    _windowIter->second->addTrackbar("bMin", &(_rgbArray[0]), 255); 
    _windowIter->second->addTrackbar("gMin", &(_rgbArray[1]), 255); 
    _windowIter->second->addTrackbar("rMin", &(_rgbArray[2]), 255); 
    _windowIter->second->addTrackbar("bMax", &(_rgbArray[3]), 255); 
    _windowIter->second->addTrackbar("gMax", &(_rgbArray[4]), 255); 
    _windowIter->second->addTrackbar("rMax", &(_rgbArray[5]), 255); 
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
*/

}
