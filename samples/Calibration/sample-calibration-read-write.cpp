/**
  * @file    sample-calibration-read-write.cpp
  * @brief   Pack a calibData struct write it to file.
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int error;
  int status;
  ImgProc::Calibration calib;
  cv::Mat eye = cv::Mat::eye(3,3,CV_8UC3);
  cv::Mat one = cv::Mat::ones(3,3,CV_8UC1);

  // Calibration Init
  calib.init(10);
  
  // Pack struct
  calib.calibData.cameraMatrix = eye.clone();
  calib.calibData.distortionCoeff = one.clone();
  for(int i=0; i<5; i++)
  {
    calib.calibData.rotationVect.push_back( eye.clone() );
    calib.calibData.translationVect.push_back( one.clone() );
  }

  // Open file
  cv::FileStorage fileNode("test.yml", cv::FileStorage::WRITE);

  // Write to file
  calib.calibData.write(fileNode, "Calib1");

  return 0;
}
