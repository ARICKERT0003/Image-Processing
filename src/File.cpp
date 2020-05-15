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
    
    _isOpen = fileStorage.open(_path.c_str(), flag);   
    
    if( _isOpen )
    { readNode = fileStorage.root(); }

    return !_isOpen;
  }

  int File::open(const std::string& directory, const std::string& fileName, const std::string&extension, int uid, int flag)
  {
    std::lock_guard<std::mutex> guard(_mu);

    init(directory, fileName, extension, uid);
    _isOpen = fileStorage.open(_path.c_str(), flag);   
    
    if( _isOpen )
    { readNode = fileStorage.root(); }

    return !_isOpen;
  }

  // ==================================
  // Image read / write
  // ==================================
  int File::read( cv::Mat& image, uint8_t modifier, int uid )
  {
    std::lock_guard<std::mutex> guard(_mu);

    if( uid != -1)
    { setUID(uid); }

    image = cv::imread( _path.c_str() );

    if( image.data == NULL )
    { return FileHandlerCodes::PathReadError; }

    if(modifier == FileModifier::NONE)
    { return FileHandlerCodes::NoError; }

    if(modifier == FileModifier::INCREMENT)
    {
      Path::operator++(1); 
      return FileHandlerCodes::NoError; 
    }

    if(modifier == FileModifier::RETURN_TO_ZERO)
    { 
      setUID(0);
      return FileHandlerCodes::NoError; 
    }

    return FileHandlerCodes::NoError; 
  }

  int File::read( std::vector< cv::Mat >& vectMat, int numMat, uint8_t modifier, int uid )  
  {
    if( uid != -1)
    { setUID(uid); }

    vectMat.resize(numMat);
    for(int i=0; i<numMat; i++)
    {
      _error = read(vectMat[i], FileModifier::INCREMENT, -1);

      if(_error)
      { return _error; }
    }

    if(modifier == FileModifier::NONE)
    { return FileHandlerCodes::NoError; }

    if(modifier == FileModifier::RETURN_TO_ZERO)
    { 
      setUID(0);
      return FileHandlerCodes::NoError; 
    }

    return FileHandlerCodes::NoError;
  }

  int File::write( const cv::Mat& image, uint8_t modifier, int uid )
  {
    std::lock_guard<std::mutex> guard(_mu);

    if( uid != -1)
    { setUID(uid); }

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

    if(modifier == FileModifier::NONE)
    { return FileHandlerCodes::NoError; }

    if(modifier == FileModifier::INCREMENT)
    {
      Path::operator++(1); 
      return FileHandlerCodes::NoError; 
    }

    if(modifier == FileModifier::RETURN_TO_ZERO)
    { 
      setUID(0);
      return FileHandlerCodes::NoError; 
    }
    
    return FileHandlerCodes::NoError; 
  }

  int File::write( const std::vector< cv::Mat >& vectMat, uint8_t modifier, int uid)
  {
    if( uid != -1)
    { setUID(uid); }

    for(int i=0; i<vectMat.size(); i++)
    {
      _error = write( vectMat[i], FileModifier::INCREMENT);

      if(_error)
      { return _error; }
    }

    if(modifier == FileModifier::NONE)
    { return FileHandlerCodes::NoError; }

    if(modifier == FileModifier::RETURN_TO_ZERO)
    { 
      setUID(0);
      return FileHandlerCodes::NoError; 
    }

    return FileHandlerCodes::NoError;
  }

  // ==================================
  // YAML read/write to node
  // ==================================
  template< typename T>
  void File::read( const std::string& nodeName, T& value)
  {
    std::lock_guard<std::mutex> guard(_mu);

    readNode[nodeName.c_str()] >> value; 
  }
  template void File::read< int         >( const std::string&, int&         );
  template void File::read< bool        >( const std::string&, bool&        );
  template void File::read< float       >( const std::string&, float&       );
  template void File::read< double      >( const std::string&, double&      );
  template void File::read< std::string >( const std::string&, std::string& );
  template void File::read< cv::Mat     >( const std::string&, cv::Mat&     );

  template< typename T>
  void File::write( const std::string& nodeName, T& value)
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << nodeName.c_str() << value; 
  } 
  template void File::write< int         >( const std::string&, int&         );
  template void File::write< bool        >( const std::string&, bool&        );
  template void File::write< float       >( const std::string&, float&       );
  template void File::write< double      >( const std::string&, double&      );
  template void File::write< std::string >( const std::string&, std::string& );
  template void File::write< cv::Mat     >( const std::string&, cv::Mat&     );

  template< typename T>
  void File::write( const std::string& nodeName, const T& value)
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << nodeName.c_str() << value; 
  } 
  template void File::write< int         >( const std::string&, const int&         );
  template void File::write< bool        >( const std::string&, const bool&        );
  template void File::write< float       >( const std::string&, const float&       );
  template void File::write< double      >( const std::string&, const double&      );
  template void File::write< std::string >( const std::string&, const std::string& );
  template void File::write< cv::Mat     >( const std::string&, const cv::Mat&     );

  template< typename T>
  void File::read( const std::string& nodeName, std::vector< T >& valueVect )
  {
    std::lock_guard<std::mutex> guard(_mu);
    //std::cout << "Root Name: " << readNode.name() << " Size " << readNode.size() << "\n"; 
    iNode = readNode.begin();
    //std::cout << "Node Name: " << (*iNode).name() << " Size " << (*iNode).size() << "\n";
    
    cv::FileNode seqNode = readNode[ nodeName.c_str() ];
    iNode = seqNode.begin();
    iNodeEnd = seqNode.end();

    for(; iNode!=iNodeEnd; iNode++)
    {
      T value;
      (*iNode) >> value;
      //matVect.push_back( tempMat.clone() );
      valueVect.push_back( value );
    }
  }
  template void File::read< int         >( const std::string&, std::vector< int         >& );
  template void File::read< bool        >( const std::string&, std::vector< bool        >& );
  template void File::read< float       >( const std::string&, std::vector< float       >& );
  template void File::read< double      >( const std::string&, std::vector< double      >& );
  template void File::read< std::string >( const std::string&, std::vector< std::string >& );
  template void File::read< cv::Mat     >( const std::string&, std::vector< cv::Mat     >& );

  template< typename T>
  void File::write( const std::string& nodeName, std::vector< T >& valueVect )
  { 
    beginSeq(nodeName);

    _mu.lock();

    for(int i=0; i<valueVect.size(); i++)
    { fileStorage << valueVect[i]; }

    _mu.unlock();

    endSeq();
  }
  template void File::write< int         >( const std::string&, std::vector< int         >& );
  template void File::write< bool        >( const std::string&, std::vector< bool        >& );
  template void File::write< float       >( const std::string&, std::vector< float       >& );
  template void File::write< double      >( const std::string&, std::vector< double      >& );
  template void File::write< std::string >( const std::string&, std::vector< std::string >& );
  template void File::write< cv::Mat     >( const std::string&, std::vector< cv::Mat     >& );

/*
  void File::read( const std::string& nodeName, std::vector< cv::Mat >& valueVect )
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    cv::FileNode seqNode = readNode[ nodeName.c_str() ];
    iNode = seqNode.begin();
    iNodeEnd = seqNode.end();

    for(; iNode != iNodeEnd; iNode++)
    {
      cv::Mat value;
      (*iNode) >> value;
      //matVect.push_back( tempMat.clone() );
      valueVect.push_back( value );
    }
  }

  void File::write( const std::string& nodeName, std::vector< cv::Mat >& valueVect )
  { 
    beginSeq(nodeName);

    _mu.lock();

    for(int i=0; i<valueVect.size(); i++)
    { fileStorage << valueVect[i]; }

    _mu.unlock();

    endSeq();
  }
*/
  // ==================================
  // YAML - Data structures
  // ==================================
  void File::beginMap( const std::string& nodeName )
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << nodeName.c_str() << "{"; 
  }

  void File::endMap()
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << "}"; 
  }

  void File::beginSeq( const std::string& nodeName )
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << nodeName.c_str() << "["; 
  }

  void File::endSeq()
  {
    std::lock_guard<std::mutex> guard(_mu);

    fileStorage << "]"; 
  }

  void File::resetReadNode()
  {
    std::lock_guard<std::mutex> guard(_mu);

    readNode = fileStorage.root(); 
  }

  void File::setReadNode(const std::string& nodeName, int nodeType, uint8_t modifier)
  {
    std::lock_guard<std::mutex> guard(_mu);

    if( modifier == FileModifier::RECURSIVE)
    { readNode = readNode[nodeName]; }
    else
    { readNode = fileStorage[nodeName]; }
    
    if(readNode.type() != nodeType)
    { readNode = fileStorage.root(); }
  }

/*
  template< typename T>
  void File::readFromStruct( const std::string& valueName, T& value) 
  {
    std::lock_guard<std::mutex> guard(_mu);
    
    readNode[valueName] >> value;
  }
  template void File::read< std::string >( cv::FileNode, const std::string&, std::string& );
  template void File::read< cv::Mat >( cv::FileNode, const std::string&, cv::Mat& );
*/
}
