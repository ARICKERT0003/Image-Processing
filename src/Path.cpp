#include "Path.h"

namespace ImgProc
{
  void Path::operator++ (int)
  {
    uid++;
    path.replace_filename( baseFileName + std::to_string(uid) + extensionType );
  }

  void Path::load(const std::string& file, const std::string& name)
  {    
    YAML::Node fileNode = YAML::LoadFile(file.c_str());

    const YAML::Node nameNode = fileNode[name.c_str()];
    load(nameNode);
  }

  void Path::load(const YAML::Node& node)
  {
    directory     = node[ "Directory"      ].as<std::string>();
    baseFileName  = node[ "Base File Name" ].as<std::string>();
    extensionType = node[ "Extension Type" ].as<std::string>();
    uid           = node[ "Starting UID"   ].as<int>();
  }

  void Path::set(const std::string& adirectory, 
                 const std::string& abaseFileName, 
                 const std::string& aextensionType,
                 int auid)
  {
    directory = adirectory;
    baseFileName = abaseFileName;
    extensionType = aextensionType;
    uid = auid;
  } 

  int Path::verifyElements()
  {
    if(directory.empty()     ||
       baseFileName.empty()  ||
       extensionType.empty() )
    { return FileHandlerCodes::MissingFileAttributes; }

    return FileHandlerCodes::NoError;
  }

  int Path::create()
  {
    file = baseFileName + std::to_string(uid) + extensionType;
    path = directory / file;
    empty = false;

    if(! std::filesystem::exists(directory, pathStatus) )
    {
      if(! std::filesystem::create_directories(directory, pathStatus) )
      { 
        std::cout << "Path construction error: " << pathStatus.message();
        return FileHandlerCodes::UnableToCreateDirectory;
      }
    }

    return FileHandlerCodes::NoError;
  }
}
