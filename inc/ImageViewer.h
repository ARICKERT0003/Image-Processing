#ifndef IMAGEVIEWER
#define IMAGEVIEWER

#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include "opencv2/opencv.hpp"
#include "Window.h"
#include "File.h"

namespace ImgProc
{
  class ImageViewer
  {
    public:
    typedef std::map<std::string, std::unique_ptr<Window>>::iterator windowIter;

    void start();
    void stop();

    int addWindow( const std::string&);
    int addWindow( const std::string&, std::shared_ptr< File >, bool=false);
    int remove(const std::string&);

    int updateWindow(std::string, cv::Mat&);

    bool getStatus();
    int getNumSavedImages(const std::string&);

    //void addTrackbarRGB(const std::string&);
    //void getTrackbarRGBValues(std::array<int,6>&);

    private:
    void _keyInterface(int);
    int _saveAll();
    void _closeAll();
    void _loop();
    bool _loopStatus = false;
    int _fhError = 0;
    std::array<int, 6> _rgbArray = {0,0,0,255,255,255};
    std::mutex _mu;
    std::thread _viewerThread;
    windowIter _windowIter;
    windowIter _loopIterBegin;
    windowIter _loopIterEnd;
    std::map<std::string, std::unique_ptr<Window>> _windowMap;
    std::pair< std::map< std::string, std::unique_ptr< Window >>::iterator, bool> _mapStatus;
  };
}

#endif
