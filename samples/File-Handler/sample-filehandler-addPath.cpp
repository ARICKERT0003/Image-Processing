/**
  * @file    sample-filehandler-addPath.cpp
  * @brief   Will add path and save images to path
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int blueError, greenError, redError;
  cv::Mat blue(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));
  cv::Mat green(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
  cv::Mat red(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));

  ImgProc::FileHandler filehandler;
  blueError  = filehandler.addPath("Blue" , "data/images", "blueImage" , ".png", 0);
  greenError = filehandler.addPath("Green", "data/images", "greenImage", ".png", 0);
  redError   = filehandler.addPath("Red"  , "data/images", "redImage"  , ".png", 0);

  if(blueError || greenError || redError)
  {
    std::cout << "\n";
    std::cout << "blueError:  " << blueError << "\n";
    std::cout << "greenError: " << greenError << "\n";
    std::cout << "redError:   " << redError << "\n";
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
