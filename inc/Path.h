#ifndef IMGPROC_PATH  
#define IMGPROC_PATH

#include <iostream>
#include <filesystem>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "ImageProcessingCodes.h"

namespace ImgProc
{
  class Path
  {
    public:
    Path();
    Path(const std::string&, const std::string&, const std::string&, int=-1);
    void init(const std::string&, const std::string&, const std::string&, int=-1);
    void operator++ (int);
    void setUID(int);
    std::string toString();
    void resetUID();
    void replaceFileName(const std::string&);
    int verifyElements();
    int makeDirectory();
    std::filesystem::path _path;

    private:
    int _uid = 0;
    std::error_code pathStatus;
    std::string _fileName;
    std::string _extension;

    std::filesystem::path _directory;
    std::filesystem::path _file;
  };
}

#endif
