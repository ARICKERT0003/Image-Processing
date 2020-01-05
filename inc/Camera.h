#ifndef IMGPROC_CAMERA  
#define IMGPROC_CAMERA

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"
#include "MediaSource.h"

namespace ImgProc
{
  class Camera : public MediaSource
  {
    public:
    Camera();
    Camera(std::string, std::string);

    int getFrame(cv::Mat&);

    //private:
    //cv::VideoCapture _stream;
    //std::string _gstPipeline;
    //int _status;
  };
}
#endif
