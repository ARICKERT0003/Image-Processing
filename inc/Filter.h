#ifndef FILTER
#define FILTER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

struct Threshold
{
  Threshold(){}

  void load(const std::string& file, const std::string& name)
  {
    YAML::Node threshDoc = YAML::LoadFile(file.c_str());

    const YAML::Node threshold = threshDoc[name.c_str()];
    threshArray = threshold[ "threshArray" ].as<std::array<int,6>>();
  }

  void setBounds()
  {
    lowerBound = cv::Scalar(threshArray[0], 
                            threshArray[1], 
                            threshArray[2]);
    upperBound = cv::Scalar(threshArray[3], 
                            threshArray[4], 
                            threshArray[5]);
  } 
    
  std::array<int,6> threshArray = {0,0,0,255,255,255};
  cv::Scalar lowerBound;
  cv::Scalar upperBound;
};

class BandFilter
{
  public:
  BandFilter();
  void setBandFilter();
  void getMask(cv::Mat&, const Threshold&, cv::Mat&);
  void filter(cv::Mat&, const Threshold&, cv::Mat&);
  void filter(cv::Mat&, cv::Mat&, cv::Mat&);

  private:
  cv::Mat _mask;
  cv::Scalar _lowerBound;
  cv::Scalar _upperBound;
};
#endif
