/**
  * @file    sample-getFrame.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include <opencv2/opencv.hpp>
#include "Camera.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat frame;
  Camera cam;
  
  status = cam.getStatus();
  std::cout << "Camera Status: " << status << "\n";

  cam.load("../config/CameraConfig.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  error = cam.getFrame(frame);
  std::cout << "Camera Error: " << error << "\n";
   
  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";
   
  return 0;
}
