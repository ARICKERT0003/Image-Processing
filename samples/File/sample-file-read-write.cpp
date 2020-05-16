/**
  * @file    sample-file-read-write.cpp
  * @brief   Will write and read images from file and compare them for
  *          similarity
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  bool test1 = false, test2 = false, test3 = false, test4 = false, test5 = false, test6 = false, test7 = false;
  int error = 0;

  // ==================================
  // Test 1 : Single image read / write
  // ==================================

  // Create File
  ImgProc::File blueFile;
  blueFile.init("data/images", "blueImage", ".png", 0);

  // Create directory
  blueFile.makeDirectory();

  // Create cv::Mats
  cv::Mat blueWrite(100, 100, CV_8UC3, cv::Scalar(255, 0, 0) );
  cv::Mat blueRead;

  // Write
  blueFile.write(blueWrite);

  // Read
  error = blueFile.read(blueRead);

  // Compare
  if(! error )
  { test1 = true; }
  
  // ==================================
  // Test 2 : Multiple image read / write
  // ==================================

  // Create File
  ImgProc::File greenFile;
  greenFile.init("data/images", "greenImage", ".png", 0);

  // Create cv::Mats
  cv::Mat greenWrite(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
  cv::Mat greenRead;

  for(int i=0; i<10; i++)
  {
    // Write images one at a time
    greenFile.write(greenWrite); 

    // Read images one at a time  
    greenFile.read(greenRead, ImgProc::FileModifier::INCREMENT); 

    // Compare
    if(! error )
    { test2 = true; }
  }

  // ==================================
  // Test 3 : Vector image read / write
  // ==================================

  // Create File
  ImgProc::File redFile;
  redFile.init("data/images", "redImage", ".png", 0);

  // Create vector of cv::Mats 
  std::vector< cv::Mat > redVectWrite, redVectRead;
  for(int i=0; i<10; i++)
  { redVectWrite.emplace_back(100, 100, CV_8UC3, cv::Scalar(0, 0, 255)); }

  // Write vector of images
  error = redFile.write(redVectWrite, ImgProc::FileModifier::RETURN_TO_ZERO);

  // Read vector of images
  error = redFile.read(redVectRead, 10);

  // Compare
  if(! error )
  { test3 = true; }

  // ==================================
  // Test 4 : YAML - Primitives
  // ==================================

  // Create File
  ImgProc::File primFile;
  primFile.init("config/prim", "primitive", ".yml");

  // Create directory
  primFile.makeDirectory();

  // Open in write mode
  primFile.open(cv::FileStorage::Mode::WRITE);

  // Create primitives
  int ir = 0, iw = 5;
  bool br = true, bw = false;
  float fr = 0.00, fw = 1.95;
  double dr = 0.0000000000, dw = 155555555.99999999;

  // Write primitives
  primFile.write("int", iw);
  primFile.write("bool", bw);
  primFile.write("float", fw);
  primFile.write("double", dw);

  // Open in read mode
  primFile.open(cv::FileStorage::Mode::READ);

  // Read primitives
  primFile.read("int", ir);
  primFile.read("bool", br);
  primFile.read("float", fr);
  primFile.read("double", dr);

  // Compare
  if(iw==ir && bw==br && fw==fr && dw==dr)
  { test4 = true; }
  else
  {
    std::cout << "int:    " << iw << " " << ir << "\n";
    std::cout << "bool:   " << bw << " " << br << "\n";
    std::cout << "float:  " << fw << " " << fr << "\n";
    std::cout << "double: " << dw << " " << dr << "\n";
  }

  // ==================================
  // Test 5 : YAML - STD 
  // ==================================

  // Create File
  ImgProc::File stdFile;
  stdFile.init("config/std", "standardLib", ".yml");

  // Create directory
  stdFile.makeDirectory();

  // Open in write mode
  stdFile.open(cv::FileStorage::Mode::WRITE);
  
  // Create string
  std::string ws("std::string");
  std::string rs(" ");

  // Write string
  stdFile.write("string", ws);

  // Open in read mode
  stdFile.open(cv::FileStorage::Mode::READ);

  // Read string
  stdFile.read("string", rs);

  // Compare
  if(ws.compare(rs) == 0)
  { test5 = true; }

  // ==================================
  // Test 6 : YAML - Map
  // ==================================

  // Create File
  ImgProc::File structFile;
  structFile.init("config/yamlStructs", "map", ".yml");

  // Create directory
  structFile.makeDirectory();

  // Open in write mode
  structFile.open(cv::FileStorage::Mode::WRITE);

  // Create values
  int wIntVal = 9, rIntVal = 0;
  float wFlVal = 7.3944, rFlVal = 0.00;
  cv::Mat wMatVal = cv::Mat::eye(6, 6, CV_8UC1);
  cv::Mat rMatVal;

  // Write
  structFile.beginMap("Map1");
  structFile.write("integer", wIntVal);
  structFile.write("float", wFlVal);
  structFile.write("Mat", wMatVal);
  structFile.endMap();

  // Open in write mode
  structFile.open(cv::FileStorage::Mode::READ);

  // Read
  structFile.setReadNode("Map1", cv::FileNode::MAP); 
  structFile.read("integer", rIntVal);
  structFile.read("float", rFlVal);
  structFile.read("Mat", rMatVal);
  structFile.resetReadNode();

  // Compare
  if(rIntVal == wIntVal && rFlVal == wFlVal)
  { test6 = true; }

  // ==================================
  // Test 7 : YAML - Seq
  // ==================================

  // Create File
  structFile.replaceFileName("seq");

  // Open in write mode
  structFile.open(cv::FileStorage::Mode::WRITE);
  
  // Create values
  std::vector< int > wIVect, rIVect;
  std::vector< float > wFVect, rFVect;
  std::vector< cv::Mat > wMVect, rMVect;
  for(int i=0; i<5; i++)
  {
    wIVect.push_back(i*7);
    wFVect.push_back(i*1.234);
    wMVect.emplace_back(cv::Mat::eye(6, 6, CV_8UC1));
  }

  // Write
  structFile.write("Seq1", wIVect);
  structFile.write("Seq2", wFVect);
  structFile.write("Seq3", wMVect);

  // Open in write mode
  structFile.open(cv::FileStorage::Mode::READ);

  // Read
  structFile.resetReadNode();
  structFile.read("Seq1", rIVect);
  structFile.read("Seq2", rFVect);
  structFile.read("Seq3", rMVect);
  structFile.resetReadNode();

  // Compare
  if(wIVect.size()==rIVect.size() && wFVect.size()==rFVect.size() && wMVect.size()==rMVect.size())
  { test7 = true; }
  else
  {
    std::cout << "Size: " << wIVect.size() << " " << rIVect.size() << "\n";
    std::cout << "Size: " << wFVect.size() << " " << rFVect.size() << "\n";
    std::cout << "Size: " << wMVect.size() << " " << rMVect.size() << "\n";
  }

  // ==================================
  // Overview
  // ==================================

  std::cout << "Status\n";
  std::cout << "test 1: " << test1 << "\n";
  std::cout << "test 2: " << test2 << "\n";
  std::cout << "test 3: " << test3 << "\n";
  std::cout << "test 4: " << test4 << "\n";
  std::cout << "test 5: " << test5 << "\n";
  std::cout << "test 6: " << test6 << "\n";
  std::cout << "test 7: " << test7 << "\n";

  return 0;
}
