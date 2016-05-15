#include <iostream>
#include <opencv2/opencv.hpp>



int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        std::cout << "Usage: " << std::endl;
        return -1;
    }
    
    cv::Mat inputImage;
    inputImage = cv::imread( argv[1], 1 );
    
    if( !inputImage.data )
    {
        std::cout << "No image data" << std::endl;
        return -1;
    }
    
    cv::namedWindow( "Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Display Image", inputImage );
    
    cv::waitKey(0);

    return 0;

}

