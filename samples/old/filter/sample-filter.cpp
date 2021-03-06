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
  cv::Mat frameA, frameB, hsv, mask;
  Threshold threshold;
  BandPass bandpass;
  ImageViewer viewer;
  MediaPipeline media;
  
  viewer.addWindow("J1Image");
  viewer.setWriteDir("J1Image", "../data/filter/J1Image/image");
  //viewer.addWindow("TrackBars");
  //viewer.addTrackbarRGB("Trackbars"); 
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

    viewer.getTrackbarRGBValues(threshold.threshArray);
    threshold.setBounds();
    bandpass.getMask(hsv, threshold, mask);
    bandpass.filter(frameA, mask, frameB);

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
