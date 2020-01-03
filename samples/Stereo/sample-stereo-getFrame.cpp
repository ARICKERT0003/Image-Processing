/**
  * @file    sample-stereo-getFrame.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat frameA, frameB;
  ImgProc::Stereo stereo;
  
  status = stereo.getStatus();
  std::cout << "Stereo Status: " << status << "\n";

  stereo.init(ImgProc::StereoCodes::Camera);
  stereo.loadCameraPair("config/CameraConfig.yaml", 
                        "CameraJ1",
                        "config/CameraConfig.yaml",
                        "CameraJ2" );
  
  error = stereo.connect();
  status = stereo.getStatus();
  std::cout << "Stereo Error: " << error << "\n";
  std::cout << "Stereo Status: " << status << "\n";

  error = stereo.getFramePair(frameA, frameB);
  std::cout << "Stereo Error: " << error << "\n";

  //cv::imshow("FrameA", frameA);
  cv::imshow("FrameB", frameB);
  cv::waitKey(0);
   
  error = stereo.disconnect();
  status = stereo.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";
   
  return 0;
}
