#include "Camera.h"

namespace ImgProc
{
  Camera::Camera()
  {
    _status = MediaSourceCodes::NotConnected;
  }

  Camera::Camera(std::string configAddr, std::string camName)
  { 
    _status = MediaSourceCodes::NotConnected;
    load(configAddr, camName); 
  }

  int Camera::getFrame(cv::Mat& frame)
  {
    _stream.read(frame);

    if( frame.empty() )
    { return MediaSourceCodes::ReturnedEmptyFrame; }

    cv::cvtColor(frame, frame, CV_YUV2BGR_I420);

    return MediaSourceCodes::NoError;
  }
}

