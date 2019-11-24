/**
  * @file    sample-getFrame.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "Camera.h"
#include "Stereo.h"
#include "ImageViewer.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat frameA, frameB;
  Stereo stereo;
  ImageViewer viewer;
  
  viewer.addWindow("J1Image");
  viewer.setWriteDir("J1Image", "../data/StereoCalib/J1Image/image");
  viewer.addWindow("J3Image");
  viewer.setWriteDir("J3Image", "../data/StereoCalib/J3Image/image");
  viewer.start();
  
  status = stereo.getStatus();
  std::cout << "Stereo Status: " << status << "\n";

  stereo.loadCameraPair("../config/CameraConfig.yaml", 
                        "CameraJ1",
                        "../config/CameraConfig.yaml",
                        "CameraJ3" );
  
  error = stereo.connect();
  status = stereo.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  stereo.getFramePair(frameA, frameB);
  //std::cout << "Camera Error: " << error << "\n";
  //std::cout << "FrameA Size: " << frameA.size() << "\n";
  std::cout << "FrameB Size: " << frameB.size() << "\n";

  cv::cvtColor(frameA, frameA, CV_YUV2BGR_I420);
  cv::cvtColor(frameB, frameB, CV_YUV2BGR_I420);
  viewer.updateWindow("J1Image", frameA);
  viewer.updateWindow("J3Image", frameB);
  usleep(5000000);
   
  error = stereo.disconnect();
  status = stereo.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  viewer.stop();
   
  return 0;
}
