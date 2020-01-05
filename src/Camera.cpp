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
    std::cout << "Camera::getFrame\n";
    std::cout << "Camera::_gstPipeline" << _gstPipeline << "\n";
    std::cout << "Camera::_status"      << _status << "\n";

    _stream.read(frame);

    if( frame.empty() )
    { return MediaSourceCodes::ReturnedEmptyFrame; }

    cv::cvtColor(frame, frame, CV_YUV2BGR_I420);

    return MediaSourceCodes::NoError;
  }
}

