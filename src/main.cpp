#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

#include "Converter.hpp"

int main( int argc, char** argv )
{
    if( argc < 2 )
    {
        throw std::runtime_error( "No image filepath provided. Aborting." );
    }
    std::cout << "You are using OpenCV version: " 
              << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << std::endl;


    Converter converter( argv[1] );
    converter.Convert();

    return 0;
}

