#include "CalibHandler.h"

namespace ImgProc
{

  void Calibration::load( const std::string& file, 
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
 
  _findCornersFlags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
  _termCriteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON);
}
