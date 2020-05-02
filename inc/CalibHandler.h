/**
 *  @file    CalibHandler.h
 *  @author  Alex Rickert
 *  @date    04/28/2020
 *  @version 1.0
 */

#ifndef IMGPROC_CALIBHANDLER
#define IMGPROC_CALIBHANDLER

#include <iostream>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>

class CalibHandler   
{

  /**
   *  @fn    load
   *  @brief Loads all data needed into specifed calibration 
   *  @param calibName Target calibration
   *  @param fileName Name of file which contains calibration data 
   *  @param settingsNodeName Name of node whch contains calibration settings
   *  @param boardNodeName Name of node which contains calibration board
   */
  void load(const std::string&, const std::string&, const std::string&, const std::string&);

  /**
   *  @fn    loadBoard
   *  @brief Loads calibration board data from file
   *  @param fileName Name of file which contains calibration board data
   *  @param nodeName Name of YAML node which contains specific board data
   */
  void loadBoard(const std::string&, const std::string&);

  /**
   *  @fn    loadSettings
   *  @brief Loads calibration settings from file
   *  @param fileName Name of file which contains calibration settings
   *  @param nodeName Name of YAML node which contains calibration settings
   */
  void loadSettings(const std::string&, const std::string&);

  FileHandler _fileHandler;
  Checkerboard _calibBoard;

  std::map< std::string, std::unique_ptr< Calibration > > _calibMap;
  std::map< std::string, std::unique_ptr< Calibration > >::iterator _iCalibData;
};

#endif
