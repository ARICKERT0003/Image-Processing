/**
  * @file    sample-connect.cpp
  * @brief   Will connect to stereo source
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
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
 
  error = stereo.disconnect();
  status = stereo.getStatus();
  std::cout << "Stereo Error: " << error << "\n";
  std::cout << "Stereo Status: " << status << "\n";
   
  return 0;
}
