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

  /**
   *  @class Calibration
   *  @brief Finds and stores intrinsic and extrinsic parameters of camera 
   */
  class Calibration
  {
    public:

    /**
     *  @fn    Calibration
     *  @brief Empty constructor
     */
    Calibration(){}

    /**
     *  @fn    init
     *  @brief Initializes calibration instance based on number of images users
     *         wants to use
     *  @param numImages Number of images to use when calibrating
     */
    void init(int);

    /**
     *  @fn    load
     *  @brief Loads fileHandler and Board data from YAML files. 
     *  @param file YAML file 
     *  @param calibNodeName YAML Node which holds the File-Handler and calibration board data
     *  @param fhNodeName File-Handler data
     *  @param boardNodeName Calibration board data
     */
    void load(const std::string&, const std::string&, const std::string&, const std::string&);

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
    int loadImages(const std::string&);

    /**
     *  @fn    findCorners
     *  @brief Goes through images, finds and stores corners of calibration board 
     */
    void findCorners();

    /**
     *  @fn    drawCorners
     *  @brief Draws corners on images, copies images in original vector
     */
    void drawCorners();

    /**
     *  @fn    calibrate
     *  @brief Extracts intrinsic and extrinsic parameters from data set
     */
    void Calibrate();

    private:
    bool _drawCorners = false;
    bool _statusFindCorners = false;
    int  _errorCode = 0;
    int  _numImages = 0;   
    int  _findCornersFlags = 0;
    int  _calibrateCameraFlags = 0;
    int  _calibrateCameraError = 0;

    cv::TermCriteria _termCriteria;
    cv::Mat _cameraMatrix;
    cv::Mat _distortionCoeff;
    std::vector< cv::Mat > _rotationVect;
    std::vector< cv::Mat > _translationVect;

    std::vector< bool > _statusFindCornersVect;
    std::vector< bool >::iterator _iStatus;
    std::vector< cv::Mat > _imageVect;
    std::vector< cv::Mat > _drawCornersVect;
    std::vector< cv::Mat >::iterator _iImage;
    std::vector< std::vector< cv::Vec2f >> _imgPointVectVect; 
    std::vector< std::vector< cv::Vec2f >>::iterator _iImgPointVect; 
    std::vector< std::vector< cv::Vec3f >> _objPointVectVect; 
    std::vector< std::vector< cv::Vec3f >>::iterator _iObjPointVect; 

    FileHandler _fileHandler;
    Checkerboard _calibBoard;
  };
}

#endif
