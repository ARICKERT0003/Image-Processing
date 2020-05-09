#include "File.h"

namespace ImgProc
{
  File::File()
  {}

  File::File(const std::string& directory, const std::string& fileName, const std::string& extension, int uid)
  { init(directory, fileName, extension, uid); }

  //void File::init(const std::string& directory, const std::string& fileName, const std::string& extension, int uid);
  //{ _path.init(directory, fileName, extension, uid); }

  int File::open(int flag)
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    _isOpen = fileStorage.open(_path, flag);   

    return !_isOpen;
  }

  int open(const std::string&, const std::string&, const std::string&, int=0, int=cv::FileStorage::Mode::READ);
  {
    std::lock_guard<std::mutex> guard(_mu);

    init(directory, fileName, extension, uid);
    _isOpen = fileStorage.open(_path, flag);   

    return !_isOpen;
  }

  cv::FileNode open(const std::string& nodeName, int nodeType);
  {
    std::lock_guard<std::mutex> guard(_mu);

    subNode = node[nodeName];
    if(rvecNode.type() != nodeType)
    { return NULL; }

    return subNode;
  }

  int File::read( cv::Mat image, bool increment )
  {
    std::lock_guard<std::mutex> guard(_mu);

    cv::imread( _path.c_str() );

    if( image.data == NULL )
    { return FileHandlerCodes::PathReadError; }

    if(increment)
    { Path::operator++(1); }

    return FileHandlerCodes::NoError; 
  }

  int File::read( std::vector< cv::Mat >& vectMat, int numMat )  
  {
    std::lock_guard<std::mutex> guard(_mu);

    vectMat.resize(numMat);
    for(int i=0; i<numMat; i++)
    {
      _error = read(vectMat[i], true);

      if(_error)
      { return _error; }
    }

    return FileHandlerCodes::NoError;
  }

  void File::read( const std::string& nodeName, T& value)
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileNode[nodeName.c_str()] >> value; 
  }
  template void File::read< cv::Mat >( const std::string&, std::string& );
  template void File::read< cv::Mat >( const std::string&, cv::Mat& );

  void read( cv::FileNode parentNode, const std::string& childNodeName, T& value) 
  {
    std::lock_guard<std::mutex> guard(_mu);

    if(parentNode == NULL)
    { return; }
    
    parentNode[childNodeName.c_str()] >> value;
  }
  template void File::read< cv::Mat >( cv::FileNode, const std::string&, std::string& );
  template void File::read< cv::Mat >( cv::FileNode, const std::string&, cv::Mat& );

  void File::read( const std::string& nodeName, std::vector< cv::Mat >& matVect )
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    subNode = fileNode[ nodeName.c_str() ];
    iNode = subNode.begin();
    iNodeEnd = subNode.end();

    for(; iNode != iNodeEnd; iNode++)
    {
      (*iNode) >> tempMat;
      matVect.push_back( tempMat.clone() );
    }
  }
  
  int File::write( const cv::Mat image, bool increment )
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    try
    { _error = cv::imwrite(_path.c_str(), image); }
    catch(const cv::Exception& ex)
    { 
      std::cout << "File::write - cv::Exception " << ex.what() << "\n"; 
      std::cout << "File::write - path " << _path.c_str() << "\n";
      return FileHandlerCodes::PathWriteError; 
    }
    if(! _error)
    { 
      std::cout << "Error:\tFile::write - Could not write " << _path.c_str() << "\n"; 
      return FileHandlerCodes::PathWriteError; 
    }

    if(increment)
    { Path::operator++(1); }
    
    return FileHandlerCodes::NoError; 
  }

  int File::write( std::vector< cv::Mat >& vectMat)
  {
    std::lock_guard<std::mutex> guard(_mu);

    for(int i=0; i<vectMat.size(); i++)
    {
      _error = write( vectMat[i], true );

      if(_error)
      { return _error; }
    }

    return FileHandlerCodes::NoError;
  }

  void File::write( const std::string& nodeName, cv::Mat& mat)
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << nodeName.c_str() << mat; 
  } 

  void File::write( const char yamlSyntax )
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << yamlSyntax; 
  }
    
  void File::write( const std::string& nodeName, const char yamlSyntax )
  { 
    std::lock_guard<std::mutex> guard(_mu);
    
    fileStorage << nodeName.c_str() << yamlSyntax; 
  }

  void File::write( const std::string& nodeName, std::vector<cv::Mat>::iterator matBegin, std::vector< cv::Mat>::iterator matEnd)
  { 
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << nodeName.c_str() << "[";
    for(; matBegin!=matEnd; matBegin++)
    { fileStorage << (*matBegin); }
    fileStorage << "]";
  }
}
