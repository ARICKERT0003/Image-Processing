#ifndef IMGPROC_CALIB
#define IMGPROC_CALIB

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "FileHandler.h"
#include "CalibrationBoard.h"

namespace ImgProc
{
  class Calibration
  {
    public:
    Calibration(){}
    void init(int);
    void load(const std::string&, const std::string&, const std::string&, const std::string&);
    void setImages(std::vector< cv::Mat >&);
    int loadImages(const std::string&);
    void findCorners();
    void drawCorners();
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
