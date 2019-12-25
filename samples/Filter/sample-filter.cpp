/**
  * @file    sample-getFrame.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "Filter.h"
#include "ImageViewer.h"
#include "MediaPipeline.h"

int main()
{
  int status = 0;
  int error = 0;
  std::array<int,6> trackBarVals; 
  cv::Mat frameA, frameB, hsv;
  cv::Mat mask, mask_C0, mask_C1, mask_C2;
  std::array<cv::Mat, 3> hsvArray;
  Threshold threshold;
  BandStop bandstop;
  BandPass bandpass;
  ImageViewer viewer;
  MediaPipeline media;
  
  viewer.addWindow("J1Image");
  viewer.setWriteDir("J1Image", "../data/filter/J1Image/image");
  viewer.addTrackbarRGB("J1Image"); 
                        
  viewer.start();

  usleep(1000);
  std::cout << "Viewer Started\n";
  
  status = media.getStatus();
  std::cout << "media Status: " << status << "\n";

  media.load("../config/VideoSrc.yaml", "Source2");
  
  error = media.connect();
  status = media.getStatus();
  std::cout << "Media Error: " << error << "\n";
  std::cout << "Media Status: " << status << "\n";

  while( viewer.getStatus() )
  {
    mask.release();
    frameB.release();

    media.getFrame(frameA);
    cv::cvtColor(frameA, hsv, cv::COLOR_BGR2HSV);
    cv::split(hsv, hsvArray.data());

    viewer.getTrackbarRGBValues(trackBarVals);
    threshold.threshVect.insert(threshold.threshVect.begin(), std::begin(trackBarVals), std::end(trackBarVals));

    threshold.setBounds();

    bandstop.getMask(hsvArray[0], threshold.threshVect[0], threshold.threshVect[3], mask_C0);
    bandpass.getMask(hsvArray[1], threshold.threshVect[1], threshold.threshVect[4], mask_C1);
    bandpass.getMask(hsvArray[2], threshold.threshVect[2], threshold.threshVect[5], mask_C2);
    cv::bitwise_and(mask_C0, mask_C1, mask, mask_C2);

    bandstop.filter(frameA, mask, frameB);

    viewer.updateWindow("J1Image", frameB);

    usleep(100000);
  }
   
  error = media.disconnect();
  status = media.getStatus();
  std::cout << "Media Error: " << error << "\n";
  std::cout << "Media Status: " << status << "\n";

  viewer.stop();
   
  return 0;
}
