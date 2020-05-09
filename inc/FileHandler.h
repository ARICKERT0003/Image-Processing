#ifndef IMGPROC_FILEHANDLER  
#define IMGPROC_FILEHANDLER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"
#include "File.h"

namespace ImgProc
{
  typedef std::map< std::string, std::shared_ptr< File > >::const_iterator fileIterator;
  typedef std::shared_ptr< File > ptrFile;

  class FileHandler
  {
    public:
    int addFile(const std::string&, const std::string&, const std::string&, const std::string&, int=0);
    int create();
    ptrFile operator[](const std::string& keyName); 
    ptrFile getIterator(const std::string&);
    void load(const std::string&, const std::string&);
    int load(const std::string&, const YAML::Node&);
    
    private:
    int _fhError;
    std::pair< std::map< std::string, std::shared_ptr< File >>::iterator, bool> _mapStatus;
    std::map< std::string, std::shared_ptr< File > >::iterator _iFile;
    std::map< std::string, std::shared_ptr< File > > _fileMap;
  };
}
#endif
