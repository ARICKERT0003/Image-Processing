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
  
  // Init Viewer
  error = viewer.addWindow("CameraJ1");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  error = viewer.setPath("CameraJ1", "data/image", "J1Image", ".png");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  // Init Camera
  cam.load("config/CameraConfig.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  // Start Viewer
  viewer.start();
  
  status = viewer.getStatus();
  std::cout << "Viewer Status: " << status << "\n";

  // Start Loop
  while( viewer.getStatus() )
  {
    error = cam.getFrame(frame);
    if(error)
    {
      std::cout << "Viewer Error: " << error << "\n"; 
      break;
    }

    error = viewer.updateWindow("CameraJ1", frame);
    if(error)
    {
      std::cout << "Viewer Error: " << error << "\n"; 
      break;
    }
  }
   
  // Stop Camera
  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  // Stop Viewer
  viewer.stop();
  std::cout << "Viewer Status: " << status << "\n";
   
  return 0;
}
