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
  
  // Init Viewer
  error = viewer.addWindow("J1Image", "data/stereo", "leftImage", ".png");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  error = viewer.addWindow("J2Image", "data/stereo", "rightImage", ".png");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }
  
  // Init Stereo Camera
  status = stereo.getStatus();
  std::cout << "Stereo Status: " << status << "\n";

  stereo.init(ImgProc::StereoCodes::Camera);
  stereo.loadCameraPair("config/CameraConfig.yaml", 
                        "CameraJ1",
                        "config/CameraConfig.yaml",
                        "CameraJ2" );
  
  error = stereo.connect();
  status = stereo.getStatus();
  if( error || status)
  {
    std::cout << "Stereo Error: " << error << "\n";
    std::cout << "Stereo Status: " << status << "\n";
    return 1;
  }

  // Start Viewer
  viewer.start();

  // Start Loop
  while( viewer.getStatus() )
  {
    error = stereo.getFramePair(frameA, frameB);
    if(error)
    { 
      std::cout << "Stereo Error: " << error << "\n"; 
      break;
    }

    viewer.updateWindow("J1Image", frameA);
    if(error)
    {
      std::cout << "Viewer Error: " << error << "\n"; 
      break;
    }

    viewer.updateWindow("J2Image", frameB);
    if(error)
    {
      std::cout << "Viewer Error: " << error << "\n"; 
      break;
    }
  }

  // Stop Stereo Camera
  error = stereo.disconnect();
  status = stereo.getStatus();
  std::cout << "Stereo Error: " << error << "\n";
  std::cout << "Stereo Status: " << status << "\n";

  // Stop Viewer
  viewer.stop();
  std::cout << "Viewer Status: " << status << "\n";
   
  return 0;
}
