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
  enum File_Syntax : char
  {
    Begin_Seq = '[',
    End_Seq = ']',
    Begin_Map = '{',
    End_Map = '}'
  };

  class File : public Path 
  {
    public:
    File();
    File(const std::string&, const std::string&, const std::string&, int=0);
    //void init(const std::string&, const std::string&, const std::string&, int=0);

    int open(int=cv::FileStorage::Mode::READ);
    int open(const std::string&, const std::string&, const std::string&, int=0, int=cv::FileStorage::Mode::READ);
    cv::FileNode open(const std::string&, int);

    int  read( cv::Mat, bool=true);
    int  read( std::vector< cv::Mat >&, int );  
    
    template< typename T>
    void read( const std::string&, T& );

    void read( cv::FileNode, const std::string&, T& ); 

    void read( const std::string&, std::vector< cv::Mat >& );

    int  write( const cv::Mat, bool=true );
    int  write( std::vector< cv::Mat >& );
    void write( const std::string& , cv::Mat&);
    void write( const char yamlSyntax );
    void write( const std::string& , const char);
    void write( const std::string& , std::vector<cv::Mat>::iterator, std::vector< cv::Mat>::iterator);

    private:
    bool _isOpen;
    int _error;
    std::mutex _mu;
    cv::Mat tempMat;
    cv::FileNode fileNode;
    cv::FileNode subNode;
    cv::FileNodeIterator iNode;
    cv::FileNodeIterator iNodeEnd;
    cv::FileStorage fileStorage;
  };
}

#endif
