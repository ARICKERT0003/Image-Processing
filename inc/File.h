/**
 *  @file    File.h
 *  @author  Alex Rickert
 *  @date    05/03/2020
 *  @version 1.0
 */

#ifndef IMGPROC_FILE
#define IMGPROC_FILE

#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "Path.h"

namespace ImgProc
{
  enum FileModifier : uint8_t
  {
    NONE = 0,
    INCREMENT = 1,
    RETURN_TO_ZERO = 2,
    RECURSIVE = 3
  };

  class File : public Path 
  {
    public:
    cv::FileNode readNode;

    File();
    File(const std::string&, const std::string&, const std::string&, int=-1);
    //void init(const std::string&, const std::string&, const std::string&, int=0);

    int open(int=cv::FileStorage::Mode::READ);
    int open(const std::string&, const std::string&, const std::string&, int=-1, int=0);
    cv::FileNode getMapNode(const std::string&);

    // Image read / write
    int read( cv::Mat&, uint8_t=FileModifier::NONE, int=-1 );
    int read( std::vector< cv::Mat >&, int, uint8_t=FileModifier::NONE, int=-1 );  
    int write( const cv::Mat&, uint8_t=FileModifier::NONE, int=-1 );
    int write( const std::vector< cv::Mat >&, uint8_t=FileModifier::NONE, int=-1);
    
    // YAML - read / write 
    template< typename T>
    void read( const std::string&, T& );
    template< typename T>
    void write( const std::string&, T& );
    template< typename T>
    void write( const std::string&, const T& );
    template< typename T>
    void read( const std::string&, std::vector< T >& );
    template< typename T>
    void write( const std::string&, std::vector< T >& );
    //void read( const std::string&, std::vector< cv::Mat >& );
    //void write( const std::string&, std::vector< cv::Mat >& );

    // YAML - Data structures
    void beginMap( const std::string& );
    void endMap();
    void beginSeq( const std::string& );
    void endSeq();
    void resetReadNode();
    void setReadNode(const std::string&, int, uint8_t=FileModifier::NONE);

    //template< typename T>
    //void readFromStruct( const std::string& valueName, T& value); 

    private:
    bool _isOpen;
    int _error;
    std::mutex _mu;
    cv::Mat tempMat;
    cv::FileNodeIterator iNode;
    cv::FileNodeIterator iNodeEnd;
    cv::FileStorage fileStorage;
  };
}

#endif
