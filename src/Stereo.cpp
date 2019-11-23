#include "Stereo.h"

int Stereo::getStatus()
{
  _camStatusA = _camArray[0].getStatus();
  _camStatusB = _camArray[1].getStatus();
  if( _camStatusA==1 && _camStatusB==1 )
  { _stereoStatus = BothNotConnected; }
  else if( _camStatusA==1 )
  { _stereoStatus = NotConnectedA; }
  else if( _camStatusB==1 )
  { _stereoStatus = NotConnectedB; }
  else 
  { _stereoStatus = StereoConnected; }
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
  if( _camArray[0].connect() )
  { return ConnectionFailure; }
  if( _camArray[1].connect() )
  { return ConnectionFailure; }
  return NoError
}

int Stereo::disconnect()
{
  if( _camArray[0].disconnect() )
  { return ReleaseFailure; }
  if( _camArray[1].disconnect() )
  { return ReleaseFailure; }
  return NoError
}

int Stereo::getFramePair(cv::Mat& frameA, cv::Mat& frameB)
{
  cameraErrorA = _camArray[0].getFrame(frameA); 
  cameraErrorB = _camArray[1].getFrame(frameB); 
}

void Stereo::loadCalibData(std::string calibFile, std::string stereoName)
{ calib.load(calibFile, stereoName); }


   
