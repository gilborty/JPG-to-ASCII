#include "Converter.hpp"

/*
    "Standard" Character ramp for grey scale, black -> white
    Credit to: http://paulbourke.net/dataformats/asciiart/

    "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. "

    or, smaller but more convincing
    " .:-=+*#%@"
*/
const std::string Converter::m_BRIGHTNESS_RAMP = " .:-=+*#%@";


Converter::Converter( const std::string inputImagePath )
    : m_inputImageFilePath( inputImagePath ),
      m_outputFilePath( "Output.txt" ),
      m_outputFile( nullptr )
{
    if( m_inputImageFilePath.empty() )
    {
        throw std::runtime_error( "No file path given. Aborting." );
    }

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

    m_outputFile.open( m_outputFilePath );
}

Converter::~Converter()
{
    m_outputFile.close();
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
