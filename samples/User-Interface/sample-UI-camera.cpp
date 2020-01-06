/**
  * @file    sample-UI-camera.cpp
  * @brief   Will connect to camera and use UI to view images
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat frame;
  ImgProc::Camera cam;
  ImgProc::ImageViewer viewer;
  
  viewer.addWindow("J1Image");
  viewer.setWriteDir("J1Image", "data/image");
  viewer.start();
  
  status = cam.getStatus();
  std::cout << "Camera Status: " << status << "\n";

  cam.load("config/CameraConfig.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  while( viewer.getStatus() )
  {
    error = cam.getFrame(frame);

    if(error)
    { std::cout << "Camera Error: " << error << "\n"; }

    viewer.updateWindow("J1Image", frame);
    usleep(1000);
  }
   
  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  viewer.stop();
   
  return 0;
}
