#ifndef IMAGEVIEWER
#define IMAGEVIEWER

#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include "opencv2/opencv.hpp"

struct Window;
class ImageViewer;

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

  void setWriteDir(std::string awriteDir)
  {
    std::lock_guard<std::mutex> guard(mu);
    writeDir = awriteDir;
  }

  bool writeImage()
  { 
    writeDir += std::to_string(writeCount);
    writeStatus = cv::imwrite(writeDir, image);
    writeCount++;
    return writeStatus; 
  }

  void addTrackbar(const std::string& trackbarName, int* value, int max)
  {
    std::lock_guard<std::mutex> guard(mu);
    cv::createTrackbar(trackbarName, name, value, max);
  }

  bool writeStatus = false;
  int writeCount = 0;
  std::string name;
  std::string writeDir;
  cv::Mat image;
  std::mutex mu;
};

class ImageViewer
{
public:
  void start();
  void stop();
  bool addWindow(std::string);
  void setWriteDir(std::string, std::string);
  bool updateWindow(std::string, cv::Mat&);
  bool getStatus();
  void addTrackbarRGB(const std::string&);
  void getTrackbarRGBValues(std::array<int,6>&);

private:
  void loop();
  void saveAllImages();
  bool _loopStatus = false;
  std::array<int, 6> _rgbArray = {0,0,0,255,255,255};
  std::thread _viewerThread;
  std::map<std::string, std::unique_ptr<Window>> _windowMap;
  std::map<std::string, std::unique_ptr<Window>>::iterator _iWindow;
  std::mutex _mu;
};

#endif
