/**
  * @file    sample-getFrame.cpp
  * @brief   Will connect to camera and get frame
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
  int key = -1;
  cv::Mat frame;
  ImgProc::MediaSource cam;
  
  status = cam.getStatus();
  std::cout << "Camera Status: " << status << "\n";

  cam.load("config/CameraConfig.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  error = cam.getFrame(frame);
  std::cout << "Camera Error: " << error << "\n";
   
  cv::cvtColor(frame, frame, CV_YUV2BGR_I420);
  cv::imshow("sample-getFrame", frame);
  cv::waitKey(0);

  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";
   
  return 0;
}
