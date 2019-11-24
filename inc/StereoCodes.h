#ifndef STEREOCODES
#define STEREOCODES

namespace StereoCodes
{
  enum StatusCodes
  {
    Connected = 0,
    BothNotConnected = 1,
    NotConnectedA = 2,
    NotConnectedB = 3,
  };

  enum ErrorCodes
  {
    NoError = 0,
    ConnectionFailure = 1000,
    ReleaseFailure = 1001,
    ReturnedEmptyFrame = 1002
  };
}
#endif
