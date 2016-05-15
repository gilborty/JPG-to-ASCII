#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

unsigned char getCharacterByBrightness( int brightness )
{
    if( brightness <= 64 )
    {
        std::cout << "One" << std::endl;
        return '@';  
    }
    else if( brightness > 64 and brightness <= 128 )
    {
        std::cout << "Two" << std::endl;
        return '*';
    }
    else if( brightness > 128 and brightness <= 192 )
    {
        std::cout << "Three" << std::endl;
        return '-';
    }
    else
    {
        std::cout << "Zero" << std::endl;
        return ' ';   
    }
}


int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        std::cout << "Usage: " << std::endl;
        return -1;
    }
    std::cout << "You are using OpenCV version: " 
              << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << std::endl;
    
    cv::Mat inputImage;
    cv::Mat grayImage;
    
    std::ofstream file;
    file.open("example.txt");
    
    
    inputImage = cv::imread( argv[1], 1 );
    cv::cvtColor( inputImage, grayImage, CV_BGR2GRAY );
    
    
    if( !inputImage.data )
    {
        std::cout << "No image data" << std::endl;
        return -1;
    }
    
    for( int i = 0; i < grayImage.rows; ++i )
    {
        for( int j = 0; j < grayImage.cols; ++j )
        {
            unsigned char value = grayImage.at<unsigned char>( i, j );
            int brightness = static_cast<int>( value );
            auto fileBright = getCharacterByBrightness( brightness );
            
            file << fileBright;
            //std::cout << "Pixel value: " << static_cast<int>( value ) << std::endl;
        }
        file << '\n';
    }
    
    file.close();
    
    cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Display Image", grayImage );
    
    cv::waitKey(0);

    return 0;

}

