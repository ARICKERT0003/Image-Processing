#ifndef STEREO
#define STEREO

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "Camera.h"
#include "StereoCodes.h"

struct Calibration;
class Stereo;

struct Calibration
{
  std::string calibImageDir;
  std::vector<cv::Mat> calibImagesA;
  std::vector<cv::Mat> calibImagesB;

  void load(std::string calibFile, std::string stereoName)
  {
    YAML::Node calibDoc = YAML::LoadFile(calibFile.c_str());

    const YAML::Node calibData = calibDoc[stereoName.c_str()];
    calibImageDir = calibData[ "ImageDirectory" ].as<std::string>();
  }
};

class Camera
{
  public:
  Stereo();
  int getStatus();
  void loadCalibrationFile(std::string, std::string);
  void loadCameraPair(std::string, std::string, std::string, std::string);
  int connect();
  int disconnect();
  void getFramePair(cv::Mat&, cv::Mat&);

  private:
  int _camStatusA = NoError;
  int _camStatusB = NoError;
  int _stereoStatus = NotConnected;
  int cameraErrorA = 0;
  int cameraErrorB = 0;
  std::array< std::unique_ptr< Camera>, 2> _camArray; //= {NULL, NULL};
  Calibration calib;
};
#endif
