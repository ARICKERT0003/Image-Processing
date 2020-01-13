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
  struct Path
  {
    bool empty = true;
    int uid = 0;
    std::error_code pathStatus;
    std::string baseFileName;
    std::string basePath;
    std::string extensionType;
    std::filesystem::path directory;
    std::filesystem::path file;
    std::filesystem::path path;

    Path(){}
    void operator++ (int);
    void load(const std::string&, const std::string&);
    void load(const YAML::Node&);
    void set(const std::string&, const std::string&, const std::string&, int=0);
    int verifyElements();
    int create();
  };
}

#endif
