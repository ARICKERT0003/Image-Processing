#include "FileHandler.h"

namespace ImgProc
{
  int FileHandler::addFile( const std::string& keyName,
                            const std::string& directory,
                            const std::string& fileName,
                            const std::string& extension,
                            int uid)
  {
    _mapStatus = _fileMap.emplace( std::make_pair(keyName, std::make_shared< File >()));

    if(! _mapStatus.second )
    { return FileHandlerCodes::UnableToPlacePath; }

    _mapStatus.first->second->init(directory, fileName, extension, uid);

    return FileHandlerCodes::NoError;
  } 

  int FileHandler::create()
  {
    _iFile = _fileMap.begin();
    for(; _iFile!=_fileMap.end(); _iFile++)
    {
      if( _iFile->second->verifyElements() )
      { return FileHandlerCodes::MissingFileAttributes; }

      if( _iFile->second->makeDirectory() )
      { return FileHandlerCodes::UnableToCreateDirectory; }
    }
  }

  ptrFile FileHandler::operator[](const std::string& keyName) 
  { 
    _iFile = _fileMap.find( keyName );

    if(_iFile == _fileMap.end() )
    { return nullptr; }

    return _iFile->second;
  }

  ptrFile FileHandler::getIterator(const std::string& keyName)
  { 
    _iFile = _fileMap.find( keyName );

    if(_iFile == _fileMap.end() )
    { return nullptr; }

    return _iFile->second;
  } 
/*
  void FileHandler::load(const std::string& file, const std::string& fhNodeName)
  {
    YAML::Node fileNode = YAML::LoadFile(file.c_str());
    const YAML::Node fhNode = fileNode[fhNodeName];

    YAML::const_iterator iNode = fhNode.begin();
    for(; iNode!=fhNode.end(); iNode++)
    {
      std::string nodeName = iNode->first.as<std::string>(); 
      std::cout << "Node: " << nodeName << "\n";

      _mapStatus = _fileMap.emplace( std::make_pair(nodeName, std::make_shared< Path >()));
      if(_mapStatus.second)
      {
        std::cout << "Map insert: Success\n";
        _mapStatus.first->second->load( fhNode[nodeName] );
      }
    }
  }

  int FileHandler::load(const std::string& nodeName, const YAML::Node& fhNode)
  {
    _mapStatus = _fileMap.emplace( std::make_pair(nodeName, std::make_shared< Path >()));
    if(! _mapStatus.second )
    { return FileHandlerCodes::UnableToPlacePath; }

    std::cout << "Map insert: Success\n";
    _mapStatus.first->second->load( fhNode );
    
    return NoError;
  }

  int FileHandler::create(Path& path)
  {
    if( path.verifyElements() )
    { return FileHandlerCodes::MissingFileAttributes; }

    if( path.create() )
    { return FileHandlerCodes::UnableToCreateDirectory; }

    return FileHandlerCodes::NoError;
  }
*/
}
