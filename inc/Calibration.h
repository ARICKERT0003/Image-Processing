/**
 *  @file    Calibration.h
 *  @author  Alex Rickert
 *  @date    04/22/2020
 *  @version 1.0
 */

#ifndef IMGPROC_CALIB
#define IMGPROC_CALIB

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "FileHandler.h"
#include "CalibrationBoard.h"

namespace ImgProc
{
  enum CalibrationError
  {
    CALIB_NO_ERROR = 0,
    CALIB_CALIB_DOES_NOT_EXIST = 1000
  };

  /**
   *  @class Calibration
   *  @brief Finds and stores intrinsic and extrinsic parameters of camera 
   */
  class Calibration
  {
    public:

    struct CameraParams
    {
      cv::Mat cameraMatrix;
      cv::Mat distortionCoeff;
      std::vector< cv::Mat > rotationVect;
      std::vector< cv::Mat > translationVect;

      int read(const cv::FileNode&);
      int write(cv::FileStorage&, std::string);
    };

    struct DataSet
    {
      int numImages;
      std::vector< bool > statusFindCornersVect;
      std::vector< cv::Mat > imageVect;
      std::vector< cv::Mat > drawCornersVect;
      std::vector< std::vector< cv::Vec2f >> imgPointVectVect; 
      std::vector< std::vector< cv::Vec3f >> objPointVectVect; 

      int read(FileHandler&, std::string&, int);
      int write(FileHandler&, std::string&);
    };

    /**
     *  @fn    CalibHandler
     *  @brief Empty constructor
     */
    Calibration(){}

    /**
     *  @fn    init
     *  @brief Initializes calibration instance based on number of images users
     *         wants to use
     *  @param numImages Number of images to use when calibrating
     */
    void init(int, int, cv::TermCriteria&);

    void setFindCornersFlags(int);

    void setTermCriteria( cv::TermCriteria&);

    void setBoard( Checkerboard& );

    /**
     *  @fn    setImages
     *  @brief Sets images to use for calibration  
     *  @param imageVect Vector of images of calibration board
     */
    void setImages(std::vector< cv::Mat >&);

    /**
     *  @fn    loadImages
     *  @brief Loads images to use for calibration from file
     *  @param pathName Directory to load images from. Will load number of
     *         images specified in init
     */
    int loadImages(FileHandler& fileHandler, const std::string& loadPathName);

    /**
     *  @fn    findCorners
     *  @brief Goes through images, finds and stores corners of calibration board 
     */
    void findCorners(Checkerboard& calibBoard);

    /**
     *  @fn    drawCorners
     *  @brief Draws corners on images, copies images in original vector
     */
    void drawCorners(Checkerboard& calibBoard);

    /**
     *  @fn    calibrate
     *  @brief Extracts intrinsic and extrinsic parameters from data set
     */
    void calibrate(Checkerboard& calibBoard);

    private:
    bool _drawCorners = false;
    bool _statusFindCorners = false;
    int  _errorCode = 0;
    int  _numImages = 0;   
    int  _findCornersFlags = 0;
    int  _calibrateCameraFlags = 0;
    int  _calibrateCameraError = 0;

    CameraParams camParams;
    DataSet dataSet;

    cv::TermCriteria _termCriteria;
    std::vector< bool >::iterator _iStatus;
    std::vector< cv::Mat >::iterator _iImage;
    std::vector< cv::Mat >::iterator _iImageEnd;
    std::vector< std::vector< cv::Vec2f >>::iterator _iImgPointVect; 
    std::vector< std::vector< cv::Vec3f >>::iterator _iObjPointVect; 
  };
}

#endif
