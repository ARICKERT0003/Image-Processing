#include "Calibration.h"

namespace ImgProc
{
  void CalibHandler::init(int numImages)
  {
    _imgPointVectVect.resize(numImages);
    _findCornersFlags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
    _termCriteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON);
  }

  void CalibHandler::load(const std::string& file, 
                          const std::string& calibNodeName,
                          const std::string& fhNodeName,
                          const std::string& boardNodeName )
  {
    YAML::Node fileNode = YAML::LoadFile(file.c_str());
    const YAML::Node calibNode = fileNode[calibNodeName];

    const YAML::Node fhNode = calibNode[fhNodeName];
    _fileHandler.load(fhNodeName, fhNode);

    const YAML::Node boardNode = calibNode[boardNodeName];
    _calibBoard.load(boardNode);
  }

  void CalibHandler::setImages(std::vector< cv::Mat >& imageVect)
  {
    _numImages = imageVect.size();
    _imageVect.assign(imageVect.begin(), imageVect.end());
  }

  int CalibHandler::loadImages(const std::string& loadPathName)
  {
    _errorCode = _fileHandler.read(loadPathName, _imageVect, _numImages);
    if( _errorCode )
    { return _errorCode; }

    return GeneralCodes::NoError;
  }

  void CalibHandler::findCorners(DataSet& dataSet)
  {
    _iImage = dataSet.imageVect.begin();
    _iImgPointVect = dataSet.imgPointVectVect.begin();

    if(dataSet.imageVect.size() != dataSet.imgPointVectVect.size())
    { 
      std::cout << "Error: imageVect and imgPointVectVect size must be equal\n";
      return;
    }

    for(; _iImage!=dataSet.imageVect.end(); _iImage++, _iImgPointVect++)
    {
      _statusFindCorners = cv::findChessboardCorners(*_iImage, 
                                                     _calibBoard.gridSize, 
                                                     *_iImgPointVect, 
                                                     _findCornersFlags );

      dataSet.objPointVectVect.push_back(_calibBoard.corners);
      dataSet.statusFindCornersVect.push_back(_statusFindCorners);
    }
  }

  void CalibHandler::drawCorners(DataSet& dataSet)
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
                                _calibBoard.gridSize,
                                *_iImgPointVect,
                                *_iStatus );
    }
  }

  void CalibHandler::calibrate(Calibration& calib)
  {
    _calibrateCameraError = cv::calibrateCamera( calib.dataSet.objPointVectVect,
                                                 calib.dataSet.imgPointVectVect,
                                                 calibBoard.gridSize,
                                                 calib.camParams.cameraMatrix,
                                                 calib.camParams.distortionCoeff,
                                                 calib.camParams.rotationVect,
                                                 calib.camParams.translationVect,
                                                 _calibrateCameraFlags,
                                                 _termCriteria ); 
  }
}
