/**
  * @file    sample-UI-addWindow.cpp
  * @brief   Will connect to camera and use UI to view images
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat blue(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
  //cv::Mat green(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
  //cv::Mat red(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));
  ImgProc::ImageViewer viewer;
  
  error = viewer.addWindow("Blue");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  error = viewer.setPath("Blue", "data/image", "blueImg", ".png");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  viewer.start();
  
  status = viewer.getStatus();
  std::cout << "UI Status: " << status << "\n";
  while( viewer.getStatus() )
  {
    viewer.updateWindow("Blue", blue);
    usleep(1000);
  }
   
  viewer.stop();
   
  return 0;
}
