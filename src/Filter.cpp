#include "Filter.h"

void RangeFilter::setRangeFilter(const cv::Mat& lower, const cv::Mat& upper)
{
  _lowerBound = lower;
  _upperBound = upper;
}

void RangeFilter::setRangeFilter(const Threshold& thresh)
{
  _lowerBound = cv::Scalar(thresh.lowerB, thresh.lowerG, thresh.lowerR);
  _upperBound = cv::Scalar(thresh.upperB, thresh.upperG, thresh.upperR);
}

void RangeFilter::filter(cv::Mat& src, cv::Mat& dst)
{ cv::inRange(src, _lowerBound, _upperBound, dst); }

