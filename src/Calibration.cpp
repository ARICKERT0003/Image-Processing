#include "Calibration.h"

namespace ImgProc
{
  void Calibration::init()
  {
    _findCornersFlags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
  }

  void Calibration::load(const std::string& file, 
                         const std::string& calibNodeName,
                         const std::string& fhNodeName,
                         const std::string& boardNodeName )
  {
    YAML::Node fileNode = YAML::LoadFile(file.c_str());
    const YAML::Node calibNode = fileNode[calibNodeName];

    const YAML::Node fhNode = calibNode[fhNodeName];
    _fileHandler.load(fhNode);

    const YAML::Node boardNode = calibNode[boardNodeName];
    _calibBoard.load(boardNode);
  }

  void Calibration::loadImages()
  {
    //iImage = imageVect.begin();
    //for(int i=0; i<numImages; i++, iImage++)
    //{
    //  *iImage = cv::imread(imageDir + imageBaseName + std::to_string(i));
    //}
  }

  void Calibration::findCorners()
  {
    _iImage = _imageVect.begin();
    _iImgPointVect = _imgPointVectVect.begin();

    if(_imageVect.size() != _imgPointVectVect.size())
    { 
      std::cout << "Error: imageVect and imgPointVectVect size must be equal\n";
      return;
    }

    for(; _iImage!=_imageVect.end(); _iImage++, _iImgPointVect++)
    {
      _statusFindCorners = cv::findChessboardCorners(*_iImage, 
                                                     _calibBoard.gridSize, 
                                                     *_iImgPointVect, 
                                                     _findCornersFlags );

      _objPointVectVect.push_back(_calibBoard.corners);
      _statusFindCornersVect.push_back(_statusFindCorners);
    }
  }

  void Calibration::drawCorners()
  {
    _drawCornersVect.assign( _imageVect.begin(), _imageVect.end());
    _iStatus = _statusFindCornersVect.begin();
    _iImage = _drawCornersVect.begin();
    _iImgPointVect = _imgPointVectVect.begin();

    if(_imageVect.size() != _imgPointVectVect.size() != _statusFindCornersVect.size())
    { 
      std::cout << "Error: imageVect and imgPointVectVect size must be equal\n";
      return;
    }

    for(; _iImage!=_imageVect.end(); _iImage++, _iImgPointVect++, _iStatus)
    {
      cv::drawChessboardCorners(*_iImage,
                                _calibBoard.gridSize,
                                *_iImgPointVect,
                                *_iStatus );
    }
  }

//  void Calibration::Calibrate()
//  {
//    //_statusCalibrateCamera = cv::CalibrateCamera(
//  }

}
