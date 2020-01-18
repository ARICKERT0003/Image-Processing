#ifndef IMGPROC_CODES
#define IMGPROC_CODES

namespace ImgProc
{
  enum GeneralCodes
  {
    NoError = 0
  };

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
      UnableToPlacePath = 1000,
      MissingFileAttributes = 1001,
      UnableToCreateDirectory = 1002,
      PathDoesNotExist = 1003,
      PathReadError = 1004
    };
  }
  
  namespace StereoCodes
  {
    enum TypeCodes
    {
      General = 0,
      Camera = 1
    };

    enum StatusCodes
    {
      Connected = 0,
      BothNotConnected = 1,
      NotConnectedA = 2,
      NotConnectedB = 3
    };

    enum ErrorCodes
    {
      NoError = 0,
      ConnectionFailure = 1000,
      ReleaseFailure = 1001,
      ReturnedEmptyFrameA = 1002,
      ReturnedEmptyFrameB = 1003
    };
  }
}

#endif

