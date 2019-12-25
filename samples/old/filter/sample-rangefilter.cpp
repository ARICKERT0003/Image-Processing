/**
  * @file    sample-getFrame.cpp
  * @brief   Will connect to camera
  * @author  Alex Rickert
  */

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "Filter.h"
#include "ImageViewer.h"

int main()
{
  int status = 0;
  int error = 0;
  cv::Mat frameA, frameB;
  Threshold threshold;
  RangeFilter bandfilter
  ImageViewer viewer;
  MediaPipeline media;
  
  viewer.addWindow("J1Image");
  viewer.setWriteDir("J1Image", "../data/filter/J1Image/image");
  viewer.addTrackbarRGB("J1Image", 
                        &(threshold.lowerB),
                        &(threshold.lowerG),
                        &(threshold.lowerR),
                        &(threshold.upperB),
                        &(threshold.upperG),
                        &(threshold.upperR) );
                        
  viewer.start();

  usleep(1000);
  std::cout << "Viewer Started\n";
  
  status = media.getStatus();
  std::cout << "media Status: " << status << "\n";

  media.load("../config/VideoSrc.yaml", "Source1");
  
  error = media.connect();
  status = media.getStatus();
  std::cout << "Media Error: " << error << "\n";
  std::cout << "Media Status: " << status << "\n";

  while( viewer.getStatus() )
  {
    media.getFrame(frameA);
    std::cout << "FrameA Size: " << frameA.size() << "\n";

    bandfilter.setRangeFilter(threshold);
    bandfilter.filter(frameA);

    //cv::cvtColor(frameA, frameA, CV_YUV2BGR_I420);
    viewer.updateWindow("J1Image", frameA);

    usleep(1000);
  }
   
  error = media.disconnect();
  status = media.getStatus();
  std::cout << "Media Error: " << error << "\n";
  std::cout << "Media Status: " << status << "\n";

  viewer.stop();
   
  return 0;
}
