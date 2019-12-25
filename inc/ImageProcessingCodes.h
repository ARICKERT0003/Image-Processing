#ifndef IMGPROC_CODES
#define IMGPROC_CODES

namespace ImgProc
{
  namespace MediaSourceCodes
  {
    enum StatusCodes
    {
      Connected = 0,
      NotConnected = 1
    };

    enum ErrorCodes
    {
      NoError = 0,
      ConnectionFailure = 1000,
      ReleaseFailure = 1001,
      ReturnedEmptyFrame = 1002
    };
  }

  namespace FileHandlerCodes
  {
    enum ErrorCodes
    {
      NoError = 0,
      MissingFileAttributes = 1000
    };
  }
  
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
}

#endif

