#ifndef FILTER
#define FILTER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

struct Threshold
{
  std::array<int,6> threshArray = {0,0,0,255,255,255};
  uint8_t lowerB;
  uint8_t lowerG;
  uint8_t lowerR;
  uint8_t upperB;
  uint8_t upperG;
  uint8_t upperR;

  void tempFunc()
  {
    lowerB = threshArray[0];
    lowerG = threshArray[1];
    lowerR = threshArray[2];
    upperB = threshArray[3];
    upperG = threshArray[4];
    upperR = threshArray[5];
  }

};

class BandFilter
{
  public:
  BandFilter();
  void setBandFilter(const cv::Mat&, const cv::Mat&);
  void setBandFilter(const Threshold&);
  void getMask(cv::Mat&, cv::Mat&);
  void filter(cv::Mat&, cv::Mat&);
  void filter(cv::Mat&, cv::Mat&, cv::Mat&);

  private:
  cv::Mat _mask;
  cv::Scalar _lowerBound;
  cv::Scalar _upperBound;
};
#endif
