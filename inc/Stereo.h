#ifndef STEREO
#define STEREO

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "MediaSource.h"
#include "Camera.h"
#include "ImageProcessingCodes.h"

//struct Calibration;
class Stereo;

namespace ImgProc
{
//  struct Calibration
//  {
//    std::string calibImageDir;
//    std::vector<cv::Mat> calibImagesA;
//    std::vector<cv::Mat> calibImagesB;
//
//    void load(std::string calibFile, std::string stereoName)
//    {
//      YAML::Node calibDoc = YAML::LoadFile(calibFile.c_str());
//
//      const YAML::Node calibData = calibDoc[stereoName.c_str()];
//      calibImageDir = calibData[ "ImageDirectory" ].as<std::string>();
//    }
//  };

  class Stereo
  {
    public:
    Stereo();
    int init(int=0);
    int getStatus();
    //void loadCalibrationFile(std::string, std::string);
    void loadCameraPair(File*, std::string, File*, std::string);
    int connect();
    int disconnect();
    int getFramePair(cv::Mat&, cv::Mat&);

    private:
    int _sourceType = StereoCodes::General;
    int _camStatusA = StereoCodes::NoError;
    int _camStatusB = StereoCodes::NoError;
    int _stereoStatus = StereoCodes::BothNotConnected;
    int cameraErrorA = 0;
    int cameraErrorB = 0;
    std::array< std::unique_ptr< MediaSource>, 2> _camArray; //= {NULL, NULL};
    //Calibration calib;
  };
}
#endif
