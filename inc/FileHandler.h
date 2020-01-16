#ifndef IMGPROC_FILEHANDLER  
#define IMGPROC_FILEHANDLER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"
#include "Path.h"

namespace ImgProc
{
  class FileHandler
  {
    public:
    void load(const std::string&, const std::string&);
    void load(const YAML::Node&);
    int addPath(const std::string&, const std::string&, const std::string&, const std::string&, int=0);
    int create();
    int create(Path& path);
    int read(const std::string&, std::vector< cv::Mat >&, int);
    void save(const std::string&, const cv::Mat&);
    //void save(std::vector< std::string >&, std::vector< cv::Mat >&);

    private:
    int _fhError;
    std::pair< std::map< std::string, std::unique_ptr< Path >>::iterator, bool> _mapStatus;
    std::map< std::string, std::unique_ptr< Path > >::iterator _iPath;
    std::map< std::string, std::unique_ptr< Path > > _pathMap;
  };
}
#endif
