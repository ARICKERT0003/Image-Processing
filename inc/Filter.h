#ifndef FILTER
#define FILTER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

struct Threshold
{
  uint8_t lowerB;
  uint8_t lowerG;
  uint8_t lowerR;
  uint8_t upperB;
  uint8_t upperG;
  uint8_t upperR;
};

class RangeFilter
{
  public:
  RangeFilter();
  void setRangeFilter(const cv::Mat&, const cv::Mat&);
  void setRangeFilter(const Threshold&);
  void filter(cv::Mat&, cv::Mat&);

  private:
  cv::Mat _lowerBound;
  cv::Mat _upperBound;
};
#endif
