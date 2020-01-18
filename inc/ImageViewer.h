#ifndef IMAGEVIEWER
#define IMAGEVIEWER

#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include "opencv2/opencv.hpp"
#include <yaml-cpp/yaml.h>
#include "FileHandler.h"

struct Window;
class ImageViewer;

namespace ImgProc
{
  struct Window
  {
    Window(){}
    Window(const std::string& aName)
    { name = aName;}

    void setImage(cv::Mat& aimage)
    { 
      std::lock_guard<std::mutex> guard(mu);
      image = aimage;
    }

    int writeImage()
    { 
      if( ptrFileHandler == NULL )
      { return ImageViewerCodes::WindowPathNotSet; }

      writeStatus = ptrFileHandler->write(iPath, image);
      return writeStatus; 
    }

    void addTrackbar(const std::string& trackbarName, int* value, int max)
    {
      std::lock_guard<std::mutex> guard(mu);
      cv::createTrackbar(trackbarName, name, value, max);
    }

    bool writeStatus = false;
    std::string name;
    cv::Mat image;
    std::mutex mu;
    std::shared_ptr< FileHandler > ptrFileHandler = NULL;
    pathIterator iPath; 
  };

  class ImageViewer
  {
  public:
    void start();
    void stop();
    int addWindow(std::string);
    int addWindow( const std::string&, const std::string&, const std::string&, const std::string& );
    int setPath( const std::string&, const std::string&, const std::string&, const std::string& );
    int updateWindow(std::string, cv::Mat&);
    bool getStatus();
    void addTrackbarRGB(const std::string&);
    void getTrackbarRGBValues(std::array<int,6>&);

  private:
    void loop();
    int saveAllImages();
    bool _loopStatus = false;
    int _fhError = 0;
    std::array<int, 6> _rgbArray = {0,0,0,255,255,255};
    std::mutex _mu;
    std::thread _viewerThread;
    std::map<std::string, std::unique_ptr<Window>> _windowMap;
    std::map<std::string, std::unique_ptr<Window>>::iterator _iWindow;
    std::pair< std::map< std::string, std::unique_ptr< Window >>::iterator, bool> _mapStatus;

    std::shared_ptr< FileHandler > _ptrFileHandler = NULL;
  };
}

#endif
