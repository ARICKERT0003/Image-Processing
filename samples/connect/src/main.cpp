/**
  * @file    sample-connect.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include "Camera.h"

int main()
{
  Camera cam();
  cam.load("../config/CameraConfig.yaml", "CameraJ1");
  int status = cam.connect();
  std::cout << "Camera Status: " << status << "\n";
  return 0;
}
