/**
 *  @file    MediaSource.h
 *  @author  Alex Rickert
 *  @date    04/22/2020
 *  @version 1.0
 */

#ifndef IMGPROC_MEDIASRC  
#define IMGPROC_MEDIASRC

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"
#include "File.h"

namespace ImgProc
{
  /**
   *  @class MediaSource
   *  @brief General class for pulling media into application
   */
  class MediaSource
  {
    public:

    /**
     *  @fn    MediaSource
     *  @brief Basic constructor
     */
    MediaSource();

    /**
     *  @fn    MediaSource
     *  @brief Constructor which loads parameters from YAML file
     *  @param configAddr YAML file which contains configuration data
     *  @param camName YAML node with camera data (Assumes it camera name)
     */
    MediaSource(File*, std::string);

    /**
     *  @fn    load
     *  @brief Loads parameters from YAML file
     *  @param configAddr YAML file which contains configuration data
     *  @param camName YAML node with camera data (Assumes it camera name)
     */
    virtual void load(File*, std::string);

    /**
     *  @fn     connect
     *  @brief  Opens cv::VideoCapture to source
     *  @return error @ref MediaSourceCodes
     */
    virtual int connect();

    /**
     *  @fn     diconnect 
     *  @brief  Closes cv::VideoCapture to source
     *  @return error @ref MediaSourceCodes
     */
    virtual int disconnect();

    /**
     *  @fn     getStatus
     *  @brief  Returns stored status of instance
     *  @return status 
     */
    virtual int getStatus();

    /**
     *  @fn     getFrame
     *  @brief  Grabs frame from source
     *  @return error @ref MediaSourceCodes
     */
    virtual int getFrame(cv::Mat&);

    protected:
    cv::VideoCapture _stream;
    std::string _gstPipeline;
    int _status;
  };
}
#endif
