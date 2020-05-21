#include "Window.h"

namespace ImgProc
{
  Window::Window()
  {
    _isOpen = false;
    _enableFileWrite = false;
    _enableVectWrite = false;
    _numSaved = 0;
    _name = "";
  }

  Window::Window(const std::string& name)
  {
    _isOpen = false;
    _enableFileWrite = false;
    _enableVectWrite = false;
    _numSaved = 0;
    _name = name;
  }

  void Window::open()
  {
    cv::namedWindow(_name); 
    _isOpen = true;
  }

  void Window::close()
  {
    cv::destroyWindow(_name);
    _isOpen = false;
  }

  void Window::setName( const std::string& name)
  { _name = name; }

  void Window::enableFileWrite(std::shared_ptr< File > pFile)
  { 
    _pFile = pFile; 
    _enableFileWrite = true;
  }

  void Window::enableVectWrite()
  {
    _pMatVect = std::make_shared< std::vector< cv::Mat >>();
    _enableVectWrite = true;
  }

  void Window::setImage(const cv::Mat& image)
  { 
    std::lock_guard<std::mutex> guard(_mu);
    _image = image.clone();
  }

  int Window::getNumSaved()
  {
    std::lock_guard<std::mutex> guard(_mu);
    return _numSaved;
  }

  void Window::disableFileWrite(std::shared_ptr< File > pFile)
  {
    pFile = _pFile;
    _pFile.reset();
    _enableFileWrite = false;
  }

  void Window::disableVectWrite(std::shared_ptr< std::vector< cv::Mat >> pMatVect)
  {
    pMatVect = _pMatVect;
    _pMatVect.reset();
    _enableVectWrite = false; 
  }

  int Window::write()
  { 
    std::lock_guard<std::mutex> guard(_mu);
    _write();
    return _error;
  }

  void Window::display(int& key)
  {
    // If locked, will return
    if(! _mu.try_lock() )
    { return; }

    // If empty, will return
    if( _image.empty() )
    { 
      _mu.unlock();
      return; 
    }

    // If window not open, open
    if(! _isOpen )
    { open(); }

    // Display image
    cv::imshow(_name, _image);
    
    // Wait for key press on window
    key = cv::waitKey(10);

    // Do things based on key
    _keyInterface( key );

    // Unlock
    _mu.unlock();
  }

  int Window::_keyInterface( int key )
  {
    // If key is not lower-case char, return
    if( key < 97 )
    { return ImageViewerCodes::NoError; }

    // x - close window
    if(key == 120 )
    { close(); }

    // s - save image 
    else if(key == 115)
    { _error =  _write(); }

    return _error;
  }

  int Window::_write()
  { 
    if( _enableFileWrite )
    { _error = _pFile->write(_image); } 

    if( _enableVectWrite )
    { _pMatVect->push_back(_image); }

    _numSaved++;
    return _error; 
  }

    /*
  void Window::addTrackbar(const std::string& trackbarName, int* value, int max)
  {
    std::lock_guard<std::mutex> guard(mu);
    cv::createTrackbar(trackbarName, name, value, max);
  }
  */
}
