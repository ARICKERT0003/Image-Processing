/**
  * @file    sample-connect.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
  ImgProc::MediaSource cam;
  
  status = cam.getStatus();
  std::cout << "Camera Status: " << status << "\n";

  cam.load("config/CameraConfig.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";
 
  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";
   
  return 0;
}
