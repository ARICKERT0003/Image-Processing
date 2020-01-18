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
  ui.addWindow("J1Image");
  ui.setWriteDir("J1Image", "data/image");
  ui.start();
  usleep(1000);
  status = ui.getStatus();
  std::cout << "UI Status: " << status << "\n";

  if(error || status)
  { 
    error = cam.disconnect();
    status = cam.getStatus();
    ui.stop();
    return 1; 
  }

  // Calibration Init
  calib.init(numImages);
  calib.load("config/imgproc-config.yaml", "Calibration", "Calib-FileHandler", "Calib-Board");
  
  //error = cam.getFrame(frame);
  //std::cout << "Camera Error: " << error << "\n";
  std::cout << "Wait for a second for everything to spin up\n";
  usleep(1000000);

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
