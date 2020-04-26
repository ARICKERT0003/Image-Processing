/**
  * @file    sample-calibration-camera.cpp
  * @brief   Will use User-Interface to take 10 images with calibration board
  *          Then use those images to calibrate camera and save output to file
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int error;
  int status;
  int numImages = 10;
  int numSavedImages = 0;
  cv::Mat frame;
  ImgProc::Camera cam;
  ImgProc::ImageViewer ui;
  ImgProc::Calibration calib;

  // Camera Init 
  status = cam.getStatus();
  std::cout << "Camera Status: " << status << "\n";

  cam.load("config/imgproc-config.yaml", "CameraJ1");
  
  error = cam.connect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  if(error || status)
  { 
    error = cam.disconnect();
    status = cam.getStatus();
    return 1; 
  }

  // User-Interface Init
  error = ui.addWindow("CameraJ1", "data/calib", "J1Image", ".png");

  if(error || status)
  { 
    std::cout << "UI Error: " << error << "\n";
    error = cam.disconnect();
    status = cam.getStatus();
    return 1; 
  }

  // Calibration Init
  calib.init(numImages);
  calib.load("config/imgproc-config.yaml", "Calibration", "Calib-FileHandler", "Calib-Board");
  
  // Start UI
  ui.start();
  status = ui.getStatus();
  std::cout << "UI Status: " << status << "\n";

  // Start Loop
  while( ui.getStatus() && numSavedImages<numImages)
  {
    error = cam.getFrame(frame);
    if(error)
    {
      std::cout << "Camera Error: " << error << "\n"; 
      break;
    }

    error = ui.updateWindow("CameraJ1", frame);
    if(error)
    {
      std::cout << "Viewer Error: " << error << "\n"; 
      break;
    }

    numSavedImages = ui.getNumSavedImages( "CameraJ1" );
  }

  calib.save("Calib1");
   
  // Camera Stop
  error = cam.disconnect();
  status = cam.getStatus();
  std::cout << "Camera Error: " << error << "\n";
  std::cout << "Camera Status: " << status << "\n";

  // UI Stop
  ui.stop();
  status = ui.getStatus();
  std::cout << "UI Status: " << status << "\n";
   
  return 0;
}
