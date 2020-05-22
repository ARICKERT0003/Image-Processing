/**
  * @file    sample-ImageViewer.cpp
  * @brief   Will add windows 
  * @author  Alex Rickert
  */

#include "ImageProcessing.h"

int main()
{
  int status = 0;
  int error = 0;
  bool test1 = false, test2 = false, test3 = false, test4 = false, test5 = false, test6 = false, test7 = false;
  ImgProc::ImageViewer viewer;
  
  // ==================================
  // Test 1 : Start viewer
  // ==================================

  // Start viewer
  viewer.start();

  // Check status of viewer
  if( viewer.getStatus() )
  { test1 = true; }

  // ==================================
  // Test 2 : Add window
  // ==================================

  // Create image
  cv::Mat blue(100, 100, CV_8UC3, cv::Scalar(255, 0, 0));

  // Add window
  error = viewer.addWindow("Blue");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  // Check viewer status
  status = viewer.getStatus();
  std::cout << "UI Status: " << status << "\n";

  // Update window with image
  if( viewer.getStatus() )
  {
    viewer.updateWindow("Blue", blue);
    usleep(1000000);
  }
   
  // Remove window
  viewer.remove("Blue");

  if(! error)
  { test2 = true; }

  // ==================================
  // Test 3 : Multiple windows
  // ==================================

  // Create images
  cv::Mat green(100, 100, CV_8UC3, cv::Scalar(0, 255, 0));
  cv::Mat red(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));

  // Add window
  error = viewer.addWindow("Green");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  // Add window
  error = viewer.addWindow("Red");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  // Check viewer status
  status = viewer.getStatus();
  std::cout << "UI Status: " << status << "\n";

  // Update window with image
  if( viewer.getStatus() )
  {
    viewer.updateWindow("Green", green);
    viewer.updateWindow("Red", red);
    usleep(1000000);
  }
  
  // Remove windows
  viewer.remove("Green");
  viewer.remove("Red");

  if(! error)
  { test3 = true; }

  // ==================================
  // Test 4 : Save to vector
  // ==================================

  // Create vector
  std::shared_ptr< std::vector< cv::Mat >> cyanVect = std::make_shared< std::vector< cv::Mat >>();

  // Create images
  cv::Mat cyan(100, 100, CV_8UC3, cv::Scalar(200, 200, 0));
  
  // Add window
  error = viewer.addWindow("Cyan");
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  // Check viewer status
  status = viewer.getStatus();
  std::cout << "UI Status: " << status << "\n";

  // Update window with image
  // User should 
  //  - save image by pressing 's'
  while( viewer.getNumSavedImages("Cyan") == 0 )
  {
    viewer.updateWindow("Cyan", cyan);
    usleep(1000);
  }

  // Get number of saved images from window
  int savedCyan = viewer.getNumSavedImages("Cyan");

  // Get vector of saved images from window
  viewer.getSavedImages("Cyan", cyanVect);

  // Remove windows
  viewer.remove("Cyan");

  if(! error && savedCyan != 0 && savedCyan == cyanVect->size())
  { test4 = true; }
  
  // ==================================
  // Test 5 : Save to file
  // ==================================

  // Create File
  std::shared_ptr< ImgProc::File > purpFile = std::make_shared< ImgProc::File >();
  purpFile->init("data/images", "image", ".png", 0);
  purpFile->makeDirectory();

  // Create images
  cv::Mat purple(100, 100, CV_8UC3, cv::Scalar(200, 0, 200));
  
  // Add window
  error = viewer.addWindow("Purple", purpFile);
  if( error )
  { 
    std::cout << "UI Error: " << error << "\n";
    return 1; 
  }

  // Check viewer status
  status = viewer.getStatus();
  std::cout << "UI Status: " << status << "\n";

  // Update window with image
  // User should 
  //  - save image by pressing 's'
  while( viewer.getNumSavedImages("Purple") == 0 )
  {
    viewer.updateWindow("Purple", purple);
    usleep(1000);
  }

  // Get number of saved images from window
  int savedImages = viewer.getNumSavedImages("Purple");

  // Remove windows
  viewer.remove("Purple");

  if(! error && savedImages != 0)
  { test5 = true; }
  
  // ==================================
  // 
  // ==================================

  // Stop viewer
  std::cout << "Stop\n";
  viewer.stop();
  
  // ==================================
  // Overview
  // ==================================

  std::cout << "Status\n";
  std::cout << "test 1: " << test1 << "\n";
  std::cout << "test 2: " << test2 << "\n";
  std::cout << "test 3: " << test3 << "\n";
  std::cout << "test 4: " << test4 << "\n";
  std::cout << "test 5: " << test5 << "\n";
  //std::cout << "test 6: " << test6 << "\n";
  //std::cout << "test 7: " << test7 << "\n";

  return 0;
}
