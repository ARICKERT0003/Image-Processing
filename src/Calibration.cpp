#include "Calibration.h"

namespace ImgProc
{
  int Calibration::CameraParams::read(File* file)
  {
    // Check Rotation Vector Exist
    //const cv::FileNode rvecNode = node["Rotation Vector"];
    //if(rvecNode.type() != cv::FileNode::SEQ)
    //{ return 1; }

    // Check Translation Vector Exist
    //const cv::FileNode tvecNode = node["Translation Vector"];
    //if(tvecNode.type() != cv::FileNode::SEQ)
    //{ return 1; }

    // Set non-vector members
    file->read("Camera Matrix", cameraMatrix);
    file->read("Distortion Coefficients", distortionCoeff);

    // Pack Rotation Vector
    file->read("Rotation Vector", rotationVect);

    // Pack Translation Vector
    file->read("Translation Vector", translationVect);

    return 0;
  } 

  int Calibration::CameraParams::write(File* file, std::string nodeName)
  {
    std::vector< cv::Mat >::iterator iBegin, iEnd;

    // Open calibration mapping
    file->write(nodeName, File_Syntax::Begin_Map);

    // Write non-vector members
    file->write("Camera Matrix", cameraMatrix);
    file->write("Distortion Coefficients", distortionCoeff);

    // Write rotation vector
    iBegin = rotationVect.begin();
    iEnd = rotationVect.end();
    file->write("Rotation Vector", iBegin, iEnd);

    // Write translation vector
    iBegin = translationVect.begin();
    iEnd = translationVect.end();
    file->write("Translation Vector", iBegin, iEnd);

    // Close calibration mapping
    file->write(File_Syntax::End_Map);

    return 0;
  }

  int Calibration::DataSet::read(File* file, int numImages)
  {
    int errorCode = 0;
    errorCode = file->read(imageVect, numImages);
    if( errorCode )
    { return errorCode; }

    return GeneralCodes::NoError;
  }

  int Calibration::DataSet::write(File* file)
  {
    int errorCode = 0;
    errorCode = file->write(imageVect);
    if( errorCode )
    { return errorCode; }

    return GeneralCodes::NoError;
  }

  void Calibration::init(int numImages, int flags, cv::TermCriteria& termCriteria)
  {
    _numImages = numImages;
    dataSet.imgPointVectVect.resize(numImages);
    setFindCornersFlags(flags);
    setTermCriteria(termCriteria);
  }

  void Calibration::setFindCornersFlags(int flags)
  { _findCornersFlags = flags; }

  void Calibration::setTermCriteria( cv::TermCriteria& termCriteria )
  { _termCriteria = termCriteria; }

  void Calibration::setImages(std::vector< cv::Mat >& imageVect)
  {
    dataSet.numImages = imageVect.size();
    dataSet.imageVect.assign(imageVect.begin(), imageVect.end());
  }

  int Calibration::loadImages(File* file)
  {
    _errorCode = dataSet.read(file, _numImages);
    if( _errorCode )
    { return _errorCode; }

    return GeneralCodes::NoError;
  }

  void Calibration::findCorners(Checkerboard& calibBoard)
  {
    _iImage = dataSet.imageVect.begin();
    _iImageEnd = dataSet.imageVect.end();
    _iImgPointVect = dataSet.imgPointVectVect.begin();

    if(dataSet.imageVect.size() != dataSet.imgPointVectVect.size())
    { 
      std::cout << "Error: imageVect and imgPointVectVect size must be equal\n";
      return;
    }

    for(; _iImage!=_iImageEnd; _iImage++, _iImgPointVect++)
    {
      _statusFindCorners = cv::findChessboardCorners(*_iImage, 
                                                     calibBoard.gridSize, 
                                                     *_iImgPointVect, 
                                                     _findCornersFlags );

      dataSet.objPointVectVect.push_back(calibBoard.corners);
      dataSet.statusFindCornersVect.push_back(_statusFindCorners);
    }
  }

  void Calibration::drawCorners(Checkerboard& calibBoard)
  {
    // Copy images to drawCornersVect
    _iImage = dataSet.imageVect.begin();
    _iImageEnd = dataSet.imageVect.end();
    dataSet.drawCornersVect.assign( _iImage, _iImageEnd );

    // Set iterator values
    _iStatus = dataSet.statusFindCornersVect.begin();
    _iImage = dataSet.drawCornersVect.begin();
    _iImageEnd = dataSet.drawCornersVect.end();
    _iImgPointVect = dataSet.imgPointVectVect.begin();

    // Check vector sizes match
    if(dataSet.imageVect.size() != dataSet.imgPointVectVect.size() != dataSet.statusFindCornersVect.size())
    { 
      std::cout << "Error: imageVect and imgPointVectVect size must be equal\n";
      return;
    }

    // Draw Corners on images 
    for(; _iImage!=_iImageEnd; _iImage++, _iImgPointVect++, _iStatus++)
    {
      cv::drawChessboardCorners(*_iImage,
                                calibBoard.gridSize,
                                *_iImgPointVect,
                                *_iStatus );
    }
  }

  void Calibration::calibrate(Checkerboard& calibBoard)
  {
    _calibrateCameraError = cv::calibrateCamera( dataSet.objPointVectVect,
                                                 dataSet.imgPointVectVect,
                                                 calibBoard.gridSize,
                                                 camParams.cameraMatrix,
                                                 camParams.distortionCoeff,
                                                 camParams.rotationVect,
                                                 camParams.translationVect,
                                                 _calibrateCameraFlags,
                                                 _termCriteria ); 
  }
}
