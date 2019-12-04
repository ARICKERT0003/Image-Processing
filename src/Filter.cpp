#include "Filter.h"

// Virtual Base
Filter::Filter(){}

void Filter::setFilter()
{}

void Filter::getMask(cv::Mat& src, const Threshold& thresh, cv::Mat& dst)
{
  cv::inRange(src, thresh.lowerBound, thresh.upperBound, dst); 
}

void Filter::filter(cv::Mat& src, const Threshold& thresh, cv::Mat& dst)
{ 
  _mask.release();
  getMask(src, thresh, _mask); 
  cv::bitwise_and(src, src, dst, _mask);
}

void Filter::filter(cv::Mat& src, cv::Mat& mask, cv::Mat& dst)
{ 
  cv::bitwise_and(src, src, dst, mask);
}

// BandPass Derived
void BandPass::getMask(cv::Mat& src, const Threshold& thresh, cv::Mat& dst)
{
  cv::inRange(src, thresh.lowerBound, thresh.upperBound, dst); 
}

void BandPass::getMask(cv::Mat& src, 
                       const double lowerBound, 
                       const double upperBound, 
                       cv::Mat& dst)
{
  cv::inRange(src, lowerBound, upperBound, dst); 
}

// BandStop Derived
void BandStop::getMask(cv::Mat& src, const Threshold& thresh, cv::Mat& dst)
{
  _maskLo.release();
  _maskHi.release();

  cv::inRange(src, 0, thresh.lowerBound, _maskLo);
  cv::inRange(src, thresh.upperBound, 255, _maskHi);
  cv::bitwise_or(_maskLo, _maskHi, dst);
}

void BandStop::getMask(cv::Mat& src,
                       const double lowerBound, 
                       const double upperBound, 
                       cv::Mat& dst)
{
  _maskLo.release();
  _maskHi.release();

  cv::inRange(src, 0, lowerBound, _maskLo);
  cv::inRange(src, upperBound, 255, _maskHi);
  cv::bitwise_or(_maskLo, _maskHi, dst);
}
