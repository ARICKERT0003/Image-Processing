#include "FileHandler.h"

namespace ImgProc
{
  void FileHandler::load(const std::string& file, const std::string& fhNodeName)
  {
    YAML::Node fileNode = YAML::LoadFile(file.c_str());
    const YAML::Node fhNode = fileNode[fhNodeName];

    YAML::const_iterator iNode = fhNode.begin();
    for(; iNode!=fhNode.end(); iNode++)
    {
      std::string nodeName = iNode->first.as<std::string>(); 
      std::cout << "Node: " << nodeName << "\n";

      _mapStatus = _pathMap.emplace( std::make_pair(nodeName, std::make_unique< Path >()));
      if(_mapStatus.second)
      {
        std::cout << "Map insert: Success\n";
        _mapStatus.first->second->load( fhNode[nodeName] );
      }
    }
  }

  int FileHandler::load(const std::string& nodeName, const YAML::Node& fhNode)
  {
    _mapStatus = _pathMap.emplace( std::make_pair(nodeName, std::make_unique< Path >()));
    if(! _mapStatus.second )
    { return FileHandlerCodes::UnableToPlacePath; }

    std::cout << "Map insert: Success\n";
    _mapStatus.first->second->load( fhNode );
    
    return NoError;
  }

  int FileHandler::addPath(const std::string& nodeName,
                           const std::string& directory,
                           const std::string& baseFileName,
                           const std::string& extensionType,
                           int uid)
  {
    _mapStatus = _pathMap.emplace( std::make_pair(nodeName, std::make_unique< Path >()));
    if(! _mapStatus.second )
    { return FileHandlerCodes::UnableToPlacePath; }

    _mapStatus.first->second->set(directory, baseFileName, extensionType, uid);

    _fhError = create( *(_mapStatus.first->second) );

    if( _fhError )
    { return _fhError; }

    return FileHandlerCodes::NoError;
  } 

  int FileHandler::create(Path& path)
  {
    if( path.verifyElements() )
    { return FileHandlerCodes::MissingFileAttributes; }

    if( path.create() )
    { return FileHandlerCodes::UnableToCreateDirectory; }

    return FileHandlerCodes::NoError;
  }

  int FileHandler::create()
  {
    _iPath = _pathMap.begin();
    for(;_iPath!=_pathMap.end(); _iPath++)
    {
      if(! _iPath->second->empty )
      { continue; }

      if( _iPath->second->verifyElements() )
      { return FileHandlerCodes::MissingFileAttributes; }

      if( _iPath->second->create() )
      { return FileHandlerCodes::UnableToCreateDirectory; }
    }
  }

  pathIterator FileHandler::getIterator(const std::string& nodeName)
  { 
    pathIterator iPath = _pathMap.find(nodeName);
    return iPath;
  } 

  int FileHandler::write(pathIterator iPath, cv::Mat& image)
  {
    try
    { _fhError = cv::imwrite(iPath->second->path.c_str(), image); }
    catch(const cv::Exception& ex)
    { 
      std::cout << "FileHandler::save - cv::Exception " << ex.what() << "\n"; 
      std::cout << "FileHandler::save - Path " << iPath->second->path.c_str() << "\n";
      return FileHandlerCodes::PathWriteError; 
    }
    if(! _fhError)
    { 
      std::cout << "Error:\tFileHandler::save - Could not save " << iPath->second->path.c_str() << "\n"; 
      return FileHandlerCodes::PathWriteError; 
    }
    
    (*(iPath->second))++;
  }


  void FileHandler::save(const std::string& nodeName, const cv::Mat& image)
  {
    _iPath = _pathMap.find(nodeName);
    
    try
    { _fhError = cv::imwrite(_iPath->second->path.c_str(), image); }
    catch(const cv::Exception& ex)
    { 
      std::cout << "FileHandler::save - cv::Exception " << ex.what() << "\n"; 
      std::cout << "FileHandler::save - Path " << _iPath->second->path.c_str() << "\n";
    }
    if(! _fhError)
    { 
      std::cout << "Error:\tFileHandler::save - Could not save " << _iPath->second->path.c_str() << "\n"; 
    }
    
    (*(_iPath->second))++;
  }

  int FileHandler::read(const std::string& nodeName, std::vector< cv::Mat >& imageVect, int numImages)
  {
    _iPath = _pathMap.find(nodeName);

    if( _iPath == _pathMap.end() )
    { return FileHandlerCodes::PathDoesNotExist; }
   
    for(int i=0; i<numImages; i++)
    { 
      imageVect.push_back( cv::imread( _iPath->second->path.c_str() ) );

      if( imageVect[i].data == NULL )
      { return FileHandlerCodes::PathReadError; }
    }

    return GeneralCodes::NoError;
  }

//  void FileHandler::save(std::vector< std::string >& fileVect, std::vector< cv::Mat >& imageVect)
//  {
//    if( fileVect.size() < imageVect.size() )
//    { return; }
//
//    std::vector< std::string >::iterator iFile = fileVect.begin();
//    std::vector< cv::Mat >::iterator iImage = imageVect.begin();
//    for(; iImage!=imageVect.end(); iImage++, iFile++)
//    {
//      cv::imwrite(*iFile, *iImage);
//    }
//  }
}
