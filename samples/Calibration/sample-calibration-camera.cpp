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
  int findCornersFlags = 0;
  cv::Mat frame;
  cv::TermCriteria termCriteria;
  ImgProc::FileHandler fileHandler;
  ImgProc::Camera cam;
  ImgProc::ImageViewer ui;
  ImgProc::Calibration calib;
  ImgProc::Checkerboard calibBoard;

  // File-Handler
  fileHandler.addFile("Camera", "config", "camera-config", ".yml"); 
  fileHandler.addFile("UI-CamJ1", "data", "J1Image", ".png"); 

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

  // Calibration Board
  //calibBoard.load("config/calib-board.yml", "Calib-Board");
  findCornersFlags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
  termCriteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON);

  // Calibration Init
  calib.init(numImages, findCornersFlags, termCriteria);
  
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

  // Calibration
  //calib.loadImages("data/calib");
   
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
