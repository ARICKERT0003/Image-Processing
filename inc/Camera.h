/**
 *  @file    Camera.h
 *  @author  Alex Rickert
 *  @date    04/22/2020
 *  @version 1.0
 */

#ifndef IMGPROC_CAMERA  
#define IMGPROC_CAMERA

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"
#include "MediaSource.h"
#include "File.h"

namespace ImgProc
{
  /**
   *  @class Camera 
   *  @brief Specialized for Jetson TX2 MIPI Cameras. Wrapped over opencv and
   *         gstreamer.
   */
  class Camera : public MediaSource
  {
    public:

    /**
     *  @fn    Camera
     *  @brief Basic constructor
     */
    Camera();

    /**
     *  @fn    Camera 
     *  @brief Constructor which loads parameters from file 
     */
    Camera(File*, std::string);

    /**
     *  @fn     getFrame
     *  @brief  Gets frame from camera. Assumes conversion from YUV to BGR color
     *          space. 
     *  @return error @ref MediaSourceCodes
     */
    int getFrame(cv::Mat&);
  };
}
#endif
