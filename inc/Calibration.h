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
    CALIB_NOERROR = 0,
    CALIB_CALIB_DOES_NOT_EXIST = 1000
  };

  struct CameraParams
  {
    cv::Mat cameraMatrix;
    cv::Mat distortionCoeff;
    std::vector< cv::Mat > rotationVect;
    std::vector< cv::Mat > translationVect;

    int read(const cv::FileNode& node)
    {
      cv::Mat tempMat;
      cv::FileNodeIterator iNode;
      cv::FileNodeIterator iNodeEnd;

      // Check Rotation Vector Exist
      const cv::FileNode rvecNode = node["Rotation Vector"];
      if(rvecNode.type() != cv::FileNode::SEQ)
      { return 1; }

      // Check Translation Vector Exist
      const cv::FileNode tvecNode = node["Translation Vector"];
      if(tvecNode.type() != cv::FileNode::SEQ)
      { return 1; }

      // Set non-vector members
      node["Camera Matrix"] >> cameraMatrix;
      node["Distortion Coefficients"] >> distortionCoeff;

      // Pack Rotation Vector
      iNode = rvecNode.begin();
      iNodeEnd = rvecNode.end();
      for(; iNode != iNodeEnd; iNode++)
      {
        (*iNode) >> tempMat;
        rotationVect.push_back( tempMat.clone() );
      }

      // Pack Translation Vector
      iNode = tvecNode.begin();
      iNodeEnd = tvecNode.end();
      for(; iNode != iNodeEnd; iNode++)
      {
        (*iNode) >> tempMat;
        translationVect.push_back( tempMat.clone() );
      } 

      return 0;
    } 

    int write(cv::FileStorage& node, std::string nodeName)
    {
      std::vector< cv::Mat >::iterator iMat, iMatEnd;

      // Open calibration mapping
      node << nodeName.c_str() << "{";

      // Write non-vector members
      node << "Camera Matrix" << cameraMatrix;
      node << "Distortion Coefficients" << distortionCoeff;

      // Write rotation vector
      iMat = rotationVect.begin();
      iMatEnd = rotationVect.end();
      
      node << "Rotation Vector" << "[";
      for(; iMat != iMatEnd; iMat++)
      { node << (*iMat); }
      node << "]";

      // Write translation vector
      iMat = translationVect.begin();
      iMatEnd = translationVect.end();
      
      node << "Translation Vector" << "[";
      for(; iMat != iMatEnd; iMat++)
      { node << (*iMat); }
      node << "]";

      // Close calibration mapping
      node << "}";

      return 0;
    }
  };

  static struct DataSet
  {
    std::vector< bool > _statusFindCornersVect;
    std::vector< cv::Mat > _imageVect;
    std::vector< cv::Mat > _drawCornersVect;
    std::vector< std::vector< cv::Vec2f >> _imgPointVectVect; 
    std::vector< std::vector< cv::Vec3f >> _objPointVectVect; 

    int read(FileHandler& fh, int numImages)
    {
      _errorCode = fh.read(loadPathName, imageVect, numImages);
      if( _errorCode )
      { return _errorCode; }

      return GeneralCodes::NoError;
    }

    int write(FileHandler& fh)
    {
      _errorCode = fh.write(loadPathName, imageVect);
      if( _errorCode )
      { return _errorCode; }

      return GeneralCodes::NoError;
    }
  };

  static struct Calibration
  {
    CameraParams camParams;
    DataSet dataSet;
  };

  /**
   *  @class Calibration
   *  @brief Finds and stores intrinsic and extrinsic parameters of camera 
   */
  class CalibHandler
  {
    public:

    /**
     *  @fn    CalibHandler
     *  @brief Empty constructor
     */
    CalibHandler(){}

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
    void findCorners(DataSet&)

    /**
     *  @fn    drawCorners
     *  @brief Draws corners on images, copies images in original vector
     */
    void drawCorners(DataSet&)

    /**
     *  @fn    calibrate
     *  @brief Extracts intrinsic and extrinsic parameters from data set
     */
    void calibrate(Calibration&);

    /**
     *  
     */
    void save(std::string);

    private:
    bool _drawCorners = false;
    bool _statusFindCorners = false;
    int  _errorCode = 0;
    int  _numImages = 0;   
    int  _findCornersFlags = 0;
    int  _calibrateCameraFlags = 0;
    int  _calibrateCameraError = 0;

    cv::TermCriteria _termCriteria;

    FileHandler _fileHandler;
    Checkerboard _calibBoard;

    std::vector< bool >::iterator _iStatus;
    std::vector< cv::Mat >::iterator _iImage;
    std::vector< cv::Mat >::iterator _iImageEnd;
    std::vector< std::vector< cv::Vec2f >>::iterator _iImgPointVect; 
    std::vector< std::vector< cv::Vec3f >>::iterator _iObjPointVect; 
    
    std::map< std::string, std::unique_ptr< Calibration > > _calibMap;
    std::map< std::string, std::unique_ptr< Calibration > >::iterator _iCalibData;
  };
}

#endif
