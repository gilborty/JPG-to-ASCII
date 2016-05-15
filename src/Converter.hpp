#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

#include <chrono>
#include <ctime>

#include <string>
#include <iomanip>

#include <stdexcept>

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

class Converter
{
    public:
        Converter( const std::string inputImagePath );
        Converter( const std::string inputImagePath, const std::string outputFilePath );
        ~Converter();
        
        void Convert();
        
    private:
        static const std::string m_BRIGHTNESS_RAMP;
        static const std::string m_ARTWORK_DIR;

        std::string m_inputImageFilePath;
        std::string m_outputFilePath;

        std::ofstream m_outputFile;

        std::string getFileName(const std::string& fileNameIn );
        std::string getTimeStampedFileName( const std::string inputFileName );
        
        float mapToRange( int valueToBeMapped, int lowInputRange, int highInputRange, int lowDestRange, int highDestRange);
        unsigned char getCharacterByBrightness( float mappedBrightnessValue );
    
};
