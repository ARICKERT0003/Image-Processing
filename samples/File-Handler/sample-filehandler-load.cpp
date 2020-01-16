/**
  * @file    sample-filehandler-load.cpp
  * @brief   Will load paths and save images to path
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int error;
  cv::Mat blue(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
  cv::Mat green(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
  cv::Mat red(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));

  ImgProc::FileHandler filehandler;
  filehandler.load("config/imgproc-config.yaml", "FileHandler");
  error  = filehandler.create();

  if(error)
  {
    std::cout << "\n";
    std::cout << "error:  " << error << "\n";
    return 1;
  }
  
  for(int i=0; i<10; i++)
  {
    filehandler.save("Blue" , blue);
    filehandler.save("Green", green);
    filehandler.save("Red"  , red);
  }
    
  return 0;
}
