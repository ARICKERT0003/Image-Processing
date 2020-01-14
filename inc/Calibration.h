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
    void init();
    void load(const std::string&, const std::string&, const std::string&, const std::string&);
    void loadImages();
    void findCorners();
    void drawCorners();

    private:
    bool _drawCorners = false;
    bool _statusFindCorners = false;
    int  _findCornersFlags = 0;
    int  _numImages = 0;   

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
