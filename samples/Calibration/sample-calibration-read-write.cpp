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
  int findCornersFlags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
  cv::TermCriteria termCriteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON);
  ImgProc::Calibration calib;

  // Calibration Init
  calib.init(10, findCornersFlags, termCriteria);
  
  // Load Images

  // Open file

  // Write to file
  //calib.calibData.write(fileNode, "Calib1");

  return 0;
}
