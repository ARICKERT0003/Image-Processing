#ifndef FILTER
#define FILTER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

struct Threshold;
class Filter;
class BandPass;
class BandStop;

struct Threshold
{
  Threshold(){}

  //void init(int numChannels)
  //{ 
  //  _numChannels = numChannels; 
  //  threshVect.resize(numChannels);
  //}

  void load(const std::string& file, const std::string& name)
  {
    YAML::Node threshDoc = YAML::LoadFile(file.c_str());

    const YAML::Node threshold = threshDoc[name.c_str()];
    threshVect = threshold[ "threshVect" ].as<std::vector<int>>();
  }

  void setBounds()
  {
    lowerBound = cv::Scalar(threshVect[0], 
                            threshVect[1], 
                            threshVect[2]);
    upperBound = cv::Scalar(threshVect[3], 
                            threshVect[4], 
                            threshVect[5]);
  } 

  std::vector<int> threshVect = {0,0,0,255,255,255};
  cv::Scalar lowerBound;
  cv::Scalar upperBound;
};

class Filter
{
  public:
  Filter();
  void setFilter();
  virtual void getMask(cv::Mat&, const Threshold&, cv::Mat&);
  virtual void filter(cv::Mat&, const Threshold&, cv::Mat&);
  virtual void filter(cv::Mat&, cv::Mat&, cv::Mat&);

  private:
  cv::Mat _mask;
};

class BandPass : public Filter
{
  public:
  void getMask(cv::Mat&, const Threshold&, cv::Mat&);
  void getMask(cv::Mat&, const double, const double, cv::Mat&);

  private:
  cv::Mat _mask;
};

class BandStop : public Filter
{
  public:
  void getMask(cv::Mat&, const Threshold&, cv::Mat&);
  void getMask(cv::Mat&, const double, const double, cv::Mat&);

  private:
  cv::Mat _maskLo;
  cv::Mat _maskHi;
};

#endif
