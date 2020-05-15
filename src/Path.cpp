#include "Path.h"

namespace ImgProc
{
  Path::Path()
  {}

  Path::Path( const std::string& directory, 
              const std::string& fileName, 
              const std::string& extension,
              int uid )
  { init(directory, fileName, extension, uid); }

  void Path::init( const std::string& directory, 
                   const std::string& fileName, 
                   const std::string& extension,
                   int uid )
  {
    _directory = directory;
    _fileName = fileName;
    _extension = extension;
    _uid = uid;

    if( uid == -1)
    {  _file = _fileName + _extension; }
    else
    {  _file = _fileName + std::to_string(_uid) + _extension; }

    _path = _directory / _file;
  } 

  std::string Path::toString()
  { return _path.string(); }

  void Path::operator++ (int)
  {
    _uid++;
    _path.replace_filename( _fileName + std::to_string(_uid) + _extension );
  }
  
  void Path::setUID(int uid)
  {
    _uid = uid;
    _path.replace_filename( _fileName + std::to_string(_uid) + _extension );
  }

  void Path::resetUID()
  { 
    _uid = 0;
    _path.replace_filename( _fileName + std::to_string(_uid) + _extension );
  }
  
  void Path::replaceFileName(const std::string& fileName)
  { 
    _fileName = fileName;
    _uid = 0;
    _path.replace_filename( _fileName + std::to_string(_uid) + _extension ); 
  }

  int Path::verifyElements()
  {
    if( _directory.empty() || _fileName.empty() || _extension.empty() )
    { return FileHandlerCodes::MissingFileAttributes; }

    return FileHandlerCodes::NoError;
  }

  int Path::makeDirectory()
  {
    if(! std::filesystem::exists(_directory, pathStatus) )
    {
      if(! std::filesystem::create_directories(_directory, pathStatus) )
      { 
        std::cout << "Path construction error: " << pathStatus.message();
        return FileHandlerCodes::UnableToCreateDirectory;
      }
    }

    return FileHandlerCodes::NoError;
  }

  /*
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
    _extension = node[ "Extension Type" ].as<std::string>();
    uid           = node[ "Starting UID"   ].as<int>();
  }
  */
}
