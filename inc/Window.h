#ifndef WINDOW
#define WINDOW

#include <unistd.h>
#include <iostream>
#include <mutex>
#include "opencv2/opencv.hpp"
#include "File.h"

namespace ImgProc
{
  class Window
  {
    public:
    bool fileWriteEnabled;
    bool vectWriteEnabled;

    Window();
    Window(const std::string&);
    void open();
    void close();
    void setName( const std::string& ); 
    void enableFileWrite( std::shared_ptr< File > );
    void enableVectWrite();
    void setImage(const cv::Mat&);
    int getNumSaved();
    void getFile( std::shared_ptr< File >);
    void getVector( std::shared_ptr< std::vector< cv::Mat >> );
    void disableFileWrite( std::shared_ptr< File >);
    void disableVectWrite( std::shared_ptr< std::vector< cv::Mat >> );
    void display(int&);
    int write();
    //void addTrackbar(const std::string&, int*, int);

    private:
    bool _isOpen;
    bool _writeStatus;
    int _error;
    int _numSaved;
    std::string _name;
    cv::Mat _image;
    std::mutex _mu;
    std::shared_ptr< std::vector< cv::Mat >> _pMatVect;
    std::shared_ptr< File > _pFile;

    int _write();
    int _keyInterface( int );
  };
}

#endif
