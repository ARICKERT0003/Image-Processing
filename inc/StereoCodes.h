#ifndef STEREOCODES
#define STEREOCODES

enum StereoStatusCodes
{
  StereoConnected = 0,
  BothNotConnected = 1,
  NotConnectedA = 2,
  NotConnectedB = 3,
};

enum StereoErrorCodes
{
  NoError = 0,
  ConnectionFailure = 1000,
  ReleaseFailure = 1001,
  ReturnedEmptyFrame = 1002
};

#endif
