#include "Stereo.h"

Stereo::Stereo(){}

int Stereo::getStatus()
{
  _camStatusA = _camArray[0]->getStatus();
  _camStatusB = _camArray[1]->getStatus();
  if( _camStatusA==1 && _camStatusB==1 )
  { _stereoStatus = StereoCodes::BothNotConnected; }
  else if( _camStatusA==1 )
  { _stereoStatus = StereoCodes::NotConnectedA; }
  else if( _camStatusB==1 )
  { _stereoStatus = StereoCodes::NotConnectedB; }
  else 
  { _stereoStatus = StereoCodes::Connected; }
  return _stereoStatus;
}
     
void Stereo::loadCameraPair(std::string configFileA, 
                            std::string camNameA,
                            std::string configFileB,
                            std::string camNameB)
{
  _camArray[0] = std::make_unique< Camera>(configFileA, camNameA);
  _camArray[1] = std::make_unique< Camera>(configFileB, camNameB);
}

int Stereo::connect()
{
  if( _camArray[0]->connect() )
  { return StereoCodes::ConnectionFailure; }
  if( _camArray[1]->connect() )
  { return StereoCodes::ConnectionFailure; }
  return StereoCodes::NoError;
}

int Stereo::disconnect()
{
  if( _camArray[0]->disconnect() )
  { return StereoCodes::ReleaseFailure; }
  if( _camArray[1]->disconnect() )
  { return StereoCodes::ReleaseFailure; }
  return StereoCodes::NoError;
}

void Stereo::getFramePair(cv::Mat& frameA, cv::Mat& frameB)
{
  _camArray[0]->getFrame(frameA); 
  _camArray[1]->getFrame(frameB); 
}

void Stereo::loadCalibrationFile(std::string calibFile, std::string stereoName)
{ calib.load(calibFile, stereoName); }


   
