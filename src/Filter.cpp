#include "Filter.h"

BandFilter::BandFilter(){}

void BandFilter::setBandFilter(const Threshold& thresh)
{
  _lowerBound = cv::Scalar(thresh.lowerB, thresh.lowerG, thresh.lowerR);
  _upperBound = cv::Scalar(thresh.upperB, thresh.upperG, thresh.upperR);
}

void BandFilter::getMask(cv::Mat& src, cv::Mat& dst)
{
  cv::inRange(src, _lowerBound, _upperBound, dst); 
}

void BandFilter::filter(cv::Mat& src, cv::Mat& mask, cv::Mat& dst)
{ 
  cv::bitwise_and(src, src, dst, mask);
}

void BandFilter::filter(cv::Mat& src, cv::Mat& dst)
{ 
  _mask.release();
  cv::inRange(src, _lowerBound, _upperBound, _mask); 
  cv::bitwise_and(src, src, dst, _mask);
}
