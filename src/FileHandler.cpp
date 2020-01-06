#include "FileHandler.h"

namespace ImgProc
{
  void FileAttributes::load(const std::string& file, const std::string& name)
  {    
    YAML::Node fileNode = YAML::LoadFile(file.c_str());

    const YAML::Node nameNode = fileNode[name.c_str()];
    load(nameNode);
  }

  void FileAttributes::load(const YAML::Node& node)
  {
    directory     = node[ "Directory" ].as<std::string>();
    baseFileName  = node[ "Base File Name" ].as<std::string>();
    extensionType = node[ "Extension Type" ].as<std::string>();
    numberOfFiles = node[ "Number of Files" ].as<int>();
  }

  void FileAttributes::set(const std::string& adirectory, 
                           const std::string& abaseFileName, 
                           const std::string& aextensionType )
  {
    directory = adirectory;
    baseFileName = abaseFileName;
    extensionType = aextensionType;
  } 

  int FileAttributes::verifyElements()
  {
    if(directory     == "" ||
       baseFileName  == "" ||
       extensionType == "" )
    { return FileHandlerCodes::MissingFileAttributes; }

    return FileHandlerCodes::NoError;
  }

  int FileAttributes::makeFileVect()
  {
    if( verifyElements()!=FileHandlerCodes::NoError )
    { return FileHandlerCodes::MissingFileAttributes; }

    for(int i=0; i<numberOfFiles; i++)
    {
      fileVect.push_back(directory + 
                         baseFileName + 
                         std::to_string(i) +
                         extensionType );
    }
    return FileHandlerCodes::NoError;
  }

  void FileHandler::load(const std::string& file)
  {
    YAML::Node fileNode = YAML::LoadFile(file.c_str());
    YAML::const_iterator iNode = fileNode.begin();
    for(; iNode!=fileNode.end(); iNode++)
    {
      std::string nodeName = iNode->first.as<std::string>(); 
      std::cout << "Node: " << nodeName << "\n";
      _mapStatus = _fileAttrMap.emplace( std::make_pair(nodeName, std::make_unique< FileAttributes >()));
      if(_mapStatus.second)
      {
        std::cout << "Map insert: Success\n";
        _mapStatus.first->second->load(*iNode);
      }
    }
  }

  void FileHandler::addStream(const std::string& nodeName,
                              const std::string& directory,
                              const std::string& baseFileName,
                              const std::string& extensionType)
  {
    _mapStatus = _fileAttrMap.emplace( std::make_pair(nodeName, std::make_unique< FileAttributes >()));
    if(_mapStatus.second)
    {
      std::cout << "Map insert: Success\n";
      _mapStatus.first->second->set(directory, baseFileName, extensionType);
    }
  } 

  void FileHandler::save(std::vector< std::string >& fileVect, std::vector< cv::Mat >& imageVect)
  {
    if( fileVect.size() < imageVect.size() )
    { return; }

    std::vector< std::string >::iterator iFile = fileVect.begin();
    std::vector< cv::Mat >::iterator iImage = imageVect.begin();
    for(; iImage!=imageVect.end(); iImage++, iFile++)
    {
      cv::imwrite(*iFile, *iImage);
    }
  }
}
