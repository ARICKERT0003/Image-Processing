#ifndef IMGPROC_MEDIASRC  
#define IMGPROC_MEDIASRC

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"

namespace ImgProc
{
  class MediaSource
  {
    public:
    MediaSource();
    MediaSource(std::string, std::string);

    void load(std::string, std::string);
    int connect();
    int disconnect();
    int getStatus();
    int getFrame(cv::Mat&);

    private:
    cv::VideoCapture _stream;
    std::string _gstPipeline;
    int _status;
  };
}
#endif
