#include "PipeElements.h"

namespace PipeElements
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

  int FileAttributes::verifyElements()
  {
    if(directory     == "" ||
       baseFileName  == "" ||
       extensionType == "" ||
       numberOfFiles <= 0 )
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
}
