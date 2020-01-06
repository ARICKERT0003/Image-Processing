/**
  * @file    sample-getFrame.cpp
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
  ImgProc::ImageViewer viewer;
  
  viewer.addWindow("J1Image");
  viewer.setWriteDir("J1Image", "data/image");
  viewer.addWindow("J2Image");
  viewer.setWriteDir("J2Image", "data/image");
  viewer.start();

  usleep(1000);
  std::cout << "Viewer Started\n";
  
  status = stereo.getStatus();
  std::cout << "Stereo Status: " << status << "\n";

  stereo.init(ImgProc::StereoCodes::Camera);
  stereo.loadCameraPair("config/CameraConfig.yaml", 
                        "CameraJ1",
                        "config/CameraConfig.yaml",
                        "CameraJ2" );
  
  error = stereo.connect();
  status = stereo.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  while( viewer.getStatus() )
  {
    error = stereo.getFramePair(frameA, frameB);

    if(error)
    { std::cout << "Stereo Error: " << error << "\n"; }

    viewer.updateWindow("J1Image", frameA);
    viewer.updateWindow("J2Image", frameB);
    usleep(1000);
  }
   
  error = stereo.disconnect();
  status = stereo.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  viewer.stop();
   
  return 0;
}
