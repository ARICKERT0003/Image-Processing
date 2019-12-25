/**
  * @file    sample-getFrame.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "Camera.h"
#include "ImageViewer.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat frame;
  Camera cam;
  ImageViewer viewer;
  
  viewer.addWindow("J1Image");
  viewer.start();
  
  status = cam.getStatus();
  std::cout << "Camera Status: " << status << "\n";

  cam.load("../config/CameraConfig.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  error = cam.getFrame(frame);
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Frame Size: " << frame.size() << "\n";

  cv::cvtColor(frame, frame, CV_YUV2BGR_I420);
  viewer.updateWindow("J1Image", frame);
  usleep(5000000);
   
  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  viewer.stop();
   
  return 0;
}
