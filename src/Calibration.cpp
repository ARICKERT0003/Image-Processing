#include "Calibration.h"

namespace ImgProc
{
  int Calibration::CameraParams::read(const cv::FileNode& node)
  {
    cv::Mat tempMat;
    cv::FileNodeIterator iNode;
    cv::FileNodeIterator iNodeEnd;

    // Check Rotation Vector Exist
    const cv::FileNode rvecNode = node["Rotation Vector"];
    if(rvecNode.type() != cv::FileNode::SEQ)
    { return 1; }

    // Check Translation Vector Exist
    const cv::FileNode tvecNode = node["Translation Vector"];
    if(tvecNode.type() != cv::FileNode::SEQ)
    { return 1; }

    // Set non-vector members
    node["Camera Matrix"] >> cameraMatrix;
    node["Distortion Coefficients"] >> distortionCoeff;

    // Pack Rotation Vector
    iNode = rvecNode.begin();
    iNodeEnd = rvecNode.end();
    for(; iNode != iNodeEnd; iNode++)
    {
      (*iNode) >> tempMat;
      rotationVect.push_back( tempMat.clone() );
    }

    // Pack Translation Vector
    iNode = tvecNode.begin();
    iNodeEnd = tvecNode.end();
    for(; iNode != iNodeEnd; iNode++)
    {
      (*iNode) >> tempMat;
      translationVect.push_back( tempMat.clone() );
    } 

    return 0;
  } 

  int Calibration::CameraParams::write(cv::FileStorage& node, std::string nodeName)
  {
    std::vector< cv::Mat >::iterator iMat, iMatEnd;

    // Open calibration mapping
    node << nodeName.c_str() << "{";

    // Write non-vector members
    node << "Camera Matrix" << cameraMatrix;
    node << "Distortion Coefficients" << distortionCoeff;

    // Write rotation vector
    iMat = rotationVect.begin();
    iMatEnd = rotationVect.end();
    
    node << "Rotation Vector" << "[";
    for(; iMat != iMatEnd; iMat++)
    { node << (*iMat); }
    node << "]";

    // Write translation vector
    iMat = translationVect.begin();
    iMatEnd = translationVect.end();
    
    node << "Translation Vector" << "[";
    for(; iMat != iMatEnd; iMat++)
    { node << (*iMat); }
    node << "]";

    // Close calibration mapping
    node << "}";

    return 0;
  }

  int Calibration::DataSet::read(FileHandler& fh, std::string& loadPathName, int numImages)
  {
    int errorCode = 0;
    errorCode = fh.read(loadPathName, imageVect, numImages);
    if( errorCode )
    { return errorCode; }

    return GeneralCodes::NoError;
  }

  int Calibration::DataSet::write(FileHandler& fh, std::string& loadPathName)
  {
    int errorCode = 0;
    errorCode = fh.write(loadPathName, imageVect);
    if( errorCode )
    { return errorCode; }

    return GeneralCodes::NoError;
  }

  void Calibration::init(int numImages, int flags, cv::TermCriteria& termCriteria)
  {
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

  int Calibration::loadImages(FileHandler& fileHandler, const std::string& loadPathName)
  {
    _errorCode = fileHandler.read(loadPathName, dataSet.imageVect, dataSet.numImages);
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
