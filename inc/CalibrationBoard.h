#ifndef IMGPROC_CALIBBOARD
#define IMGPROC_CALIBBOARD

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

namespace ImgProc
{
  struct Checkerboard
  {
    cv::Size gridSize;
    cv::Size_<float> rectSize;
    std::vector< cv::Vec3f> corners;
    std::vector< cv::Vec3f>::iterator iCorner;

    void load(const std::string& file, const std::string& name)
    {
      YAML::Node fileNode = YAML::LoadFile(file.c_str());

      const YAML::Node boardNode = fileNode[name.c_str()];
      load(boardNode);
      calcCorners();
    }

    void load(const YAML::Node& boardNode)
    {
      gridSize.width  = boardNode[ "Grid Width"  ].as<int>();
      gridSize.height = boardNode[ "Grid Height" ].as<int>();
      rectSize.width  = (float)boardNode[ "Rect Width"  ].as<float>();
      rectSize.height = (float)boardNode[ "Rect Height" ].as<float>();
    }

    void calcCorners()
    {
      for(int i=0; i<(gridSize.height); i++)
      {
        for(int j=0; j<(gridSize.width); j++)
        {
          corners.emplace_back(j*rectSize.width, i*rectSize.height, 0);
        }
      }
    }

    void print()
    {
      std::cout << "gridSize-width:  " << gridSize.width << "\n";
      std::cout << "gridSize-height: " << gridSize.height << "\n";
      std::cout << "rectSize-width:  " << rectSize.width << "\n";
      std::cout << "rectSize-height: " << rectSize.height << "\n";

      std::cout << "corners:\n";
      std::vector< cv::Vec3f>::iterator iCorner = corners.begin();
      for(;iCorner!=corners.end(); iCorner++)
      {
        std::cout << "x: " << (*iCorner)[0] << " y: " << (*iCorner)[1] << " z: " << (*iCorner)[2] << "\n";
      }
    }
  };
}

#endif
