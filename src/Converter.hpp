#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <exception>


#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

class Converter
{
    public:
        Converter( const std::string inputImagePath );
        Converter( const std::string inputImagePath, const std::string outputFilePath );
        
        bool Convert();
        
    private:
        std::string m_smallerBrightnessRamp( " .:-=+*#%@" );
        std::string m_inputImageFilePath;
        
        float mapToRange( int valueToBeMapped, int lowInputRange, int highInputRange, int lowDestRange, int highDestRange);
        unsigned char getCharacterByBrightness( float mappedBrightnessValue );
    
}