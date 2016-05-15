#include "Converter.hpp"

/*
    "Standard" Character ramp for grey scale, black -> white
    Credit to: http://paulbourke.net/dataformats/asciiart/

    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. "

    or, smaller but more convincing
    " .:-=+*#%@"
*/
const std::string Converter::m_BRIGHTNESS_RAMP = " .:-=+*#%@";
const std::string Converter::m_ARTWORK_DIR = "artwork/";


Converter::Converter( const std::string inputImagePath )
    : m_inputImageFilePath( inputImagePath ),
      m_outputFilePath( "Output.txt" ),
      m_outputFile( nullptr )
{
    if( m_inputImageFilePath.empty() )
    {
        throw std::runtime_error( "No file path given. Aborting." );
    }

    m_outputFilePath = getTimeStampedFileName( m_inputImageFilePath );
    m_outputFile.open( m_outputFilePath );
}

Converter::Converter(const std::string inputImagePath, const std::string outputFilePath)
    : m_inputImageFilePath( inputImagePath ),
      m_outputFilePath( outputFilePath ),
      m_outputFile( nullptr )
{
    if( m_inputImageFilePath.empty() )
    {
        throw std::runtime_error( "No file path given. Aborting." );
    }

    m_outputFilePath = getTimeStampedFileName( m_inputImageFilePath );
    m_outputFile.open( m_outputFilePath );
}

Converter::~Converter()
{
    m_outputFile.close();
}

std::string Converter::getFileName(const std::string& fileNameIn)
{
    //Remove directory
    std::string fileNameWithoutDir = fileNameIn.substr( fileNameIn.find_last_of("/") + 1 );

    //And then remove extension
    size_t lastIndex = fileNameWithoutDir.find_last_of(".");
    return fileNameWithoutDir.substr(0, lastIndex);
}

std::string Converter::getTimeStampedFileName(const std::string inputFileName)
{
   //Log file is ISO 8601 format. Sort of... (IMAGE_NAME-YYYY-MM-DDTHH-MM-SS)
   auto now = std::chrono::system_clock::now();
   auto tt = std::chrono::system_clock::to_time_t(now);

   std::tm local_tm = *std::localtime(&tt);
   std::string fileName = getFileName( inputFileName );

   std::stringstream ss;
   ss << m_ARTWORK_DIR;
   ss << fileName << '-';
   ss << local_tm.tm_year + 1900 << '-';
   ss << local_tm.tm_mon + 1 << '-';
   ss << local_tm.tm_mday << 'T';
   ss << local_tm.tm_hour << '-';
   ss << local_tm.tm_min << '-';
   ss << local_tm.tm_sec << ".txt";

   return ss.str();

}

float Converter::mapToRange(int valueToBeMapped, int lowInputRange = 0, int highInputRange = 256, int lowDestRange = 0, int highDestRange = m_BRIGHTNESS_RAMP.length())
{
    /*
     * Credit to: http://forum.unity3d.com/threads/re-map-a-number-from-one-range-to-another.119437/
    */

    return lowDestRange + ( valueToBeMapped - lowInputRange ) * ( highDestRange - lowDestRange ) / ( highInputRange - lowInputRange );
}

unsigned char Converter::getCharacterByBrightness(float mappedBrightnessValue)
{
    return static_cast<unsigned char>( m_BRIGHTNESS_RAMP.at( mappedBrightnessValue ) );
}


void Converter::Convert()
{
    //Containters for images
    cv::Mat inputImage;

    //Read the image as gray scale and make sure there is data
    inputImage = cv::imread( m_inputImageFilePath, CV_LOAD_IMAGE_GRAYSCALE );
    if( !inputImage.data )
    {
        throw std::runtime_error( "No input image data! Aborting." );
    }

    std::cout << "Converting image: " << m_inputImageFilePath << " to ASCII." << std::endl;

    //Convert to ASCII
    for( int i = 0; i < inputImage.rows; ++i )
    {
        for( int j = 0; j < inputImage.cols; ++j )
        {
            auto pixelIntensity = static_cast<int>( inputImage.at<unsigned char>( i, j ) );
            auto mappedValue = mapToRange( pixelIntensity );
            auto ASCIICharacter = getCharacterByBrightness( mappedValue );

            m_outputFile << ASCIICharacter;
        }
        m_outputFile << '\n';
    }

    //Show the image that you are converting to ASCII
    cv::namedWindow( "Input Image", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Input Image", inputImage );

    std::cout << "Wrote ASCII image to: " << m_outputFilePath << std::endl;

    cv::waitKey(0);

}
