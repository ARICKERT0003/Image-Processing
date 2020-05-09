#include "MediaSource.h"

namespace ImgProc
{
  MediaSource::MediaSource()
  {
    _status = MediaSourceCodes::NotConnected;
  }

  MediaSource::MediaSource(std::string configAddr, std::string camName)
  { 
    _status = MediaSourceCodes::NotConnected;
    load(configAddr, camName); 
  }

  void MediaSource::load(File* file, std::string camName)
  {
    YAML::Node cfgDoc = YAML::LoadFile(configAddr.c_str());

    const YAML::Node camData = cfgDoc[camName.c_str()];
    _gstPipeline = camData[ "gstreamerString"].as<std::string>();
  }

  int MediaSource::connect()
  {
    _stream.open(_gstPipeline);
    if(!_stream.isOpened())
    { return MediaSourceCodes::ConnectionFailure; }

    _status = MediaSourceCodes::Connected;
    return MediaSourceCodes::NoError;
  }

  int MediaSource::disconnect()
  {
    _stream.release();
    if( _stream.isOpened() )
    { return MediaSourceCodes::ReleaseFailure; }

    _status = MediaSourceCodes::NotConnected;
    return MediaSourceCodes::NoError;
  }

  int MediaSource::getStatus()
  { return _status; }

  int MediaSource::getFrame(cv::Mat& frame)
  {
    std::cout << "MediaSource::getFrame\n";
    _stream.read(frame);

    if( frame.empty() )
    { return MediaSourceCodes::ReturnedEmptyFrame; }

    return MediaSourceCodes::NoError;
  }
}
