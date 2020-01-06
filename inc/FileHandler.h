#ifndef IMGPROC_FILEHANDLER  
#define IMGPROC_FILEHANDLER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"

namespace ImgProc
{
  struct FileAttributes
  {
    std::string directory;
    std::string baseFileName;
    std::string extensionType;
    int indexBegin;
    int indexEnd;
    int numberOfFiles;
    std::vector< std::string > fileVect;

    FileAttributes(){}
    void set(const std::string&, const std::string&, const std::string&);
    void load(const std::string&, const std::string&);
    void load(const YAML::Node&);
    int verifyElements();
    int makeFileVect();
  };
  
  class FileHandler
  {
    public:
    void load(const std::string&);
    void addStream(const std::string&, const std::string&, const std::string&, const std::string&);
    void save(std::vector< std::string >&, std::vector< cv::Mat >&);

    private:
    std::pair< std::map< std::string, std::unique_ptr< FileAttributes >>::iterator, bool> _mapStatus;
    std::map< std::string, std::unique_ptr< FileAttributes > > _fileAttrMap;
  };
}
#endif
