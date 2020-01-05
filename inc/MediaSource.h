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

    virtual void load(std::string, std::string);
    virtual int connect();
    virtual int disconnect();
    virtual int getStatus();
    virtual int getFrame(cv::Mat&);

    protected:
    cv::VideoCapture _stream;
    std::string _gstPipeline;
    int _status;
  };
}
#endif
