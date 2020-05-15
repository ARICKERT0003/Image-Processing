#ifndef IMAGEVIEWER
#define IMAGEVIEWER

#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include "opencv2/opencv.hpp"
#include <yaml-cpp/yaml.h>
#include "File.h"

struct Window;
class ImageViewer;

namespace ImgProc
{
  struct Window
  {
    Window(){}
    Window(const std::string& aName)
    { name = aName;}

    void display(cv::Mat& aimage)
    { 
      std::lock_guard<std::mutex> guard(mu);
      image = aimage;
    }

    int write()
    { 
      std::lock_guard<std::mutex> guard(mu);
      if( ptrFile == NULL )
      { return ImageViewerCodes::WindowPathNotSet; }

      writeStatus = ptrFile->write(image);
      if( writeStatus )
      { return writeStatus; }

      numSavedImages++;
      return writeStatus; 
    }

    void addTrackbar(const std::string& trackbarName, int* value, int max)
    {
      std::lock_guard<std::mutex> guard(mu);
      cv::createTrackbar(trackbarName, name, value, max);
    }

    bool writeStatus = false;
    int numSavedImages = 0;
    std::string name;
    cv::Mat image;
    std::mutex mu;
    std::shared_ptr< File > ptrFile = NULL;
  };

  class ImageViewer
  {
  public:
    void start();
    void stop();
    int addWindow(std::string);
    int addWindow( const std::string& winName, File& file);
    int updateWindow(std::string, cv::Mat&);
    bool getStatus();
    int getNumSavedImages(const std::string&);
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
  };
}

#endif
