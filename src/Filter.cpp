#include "Filter.h"

BandFilter::BandFilter(){}

void BandFilter::setBandFilter()
{}

void BandFilter::getMask(cv::Mat& src, const Threshold& thresh, cv::Mat& dst)
{
  cv::inRange(src, thresh.lowerBound, thresh.upperBound, dst); 
}

void BandFilter::filter(cv::Mat& src, const Threshold& thresh, cv::Mat& dst)
{ 
  _mask.release();
  cv::inRange(src, _lowerBound, _upperBound, _mask); 
  cv::bitwise_and(src, src, dst, _mask);
}

void BandFilter::filter(cv::Mat& src, cv::Mat& mask, cv::Mat& dst)
{ 
  cv::bitwise_and(src, src, dst, mask);
}
