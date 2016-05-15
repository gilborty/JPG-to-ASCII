#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>


/*
    "Standard" Character ramp for grey scale, black -> white
    Credit to: http://paulbourke.net/dataformats/asciiart/
    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. "
    or, smaller but more convincing
    "
*/

std::string brightnessRamp( "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'. " );
std::string smallerBrightnessRamp( " .:-=+*#%@" );
//std::string smallerBrightnessRamp( "@%#*+=-:. " );

float map( int value, int a1, int a2, int b1, int b2 )
{
    return b1 + ( value - a1 )* ( b2 - b1 )/(a2 -a1);
}

//Lazy mapping from brightness to char
unsigned char getCharacterByBrightness( float mappedBrightness )
{
    return static_cast<unsigned char>( smallerBrightnessRamp.at( mappedBrightness ) );
}


int main( int argc, char** argv )
{
    std::cout << "l: " << smallerBrightnessRamp.length() << std::endl;
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
            auto newValue = map( brightness, 0, 256, 0, smallerBrightnessRamp.length() );
            auto fileBright = getCharacterByBrightness( newValue );
            
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

