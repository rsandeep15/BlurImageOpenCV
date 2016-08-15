#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

Mat src; Mat normalized; Mat gaussian; Mat median; Mat bilateral; 
string window_name1 = "UnprocessedImage";
string window_name2 = "NormalizedBlur";
string window_name3 = "GaussianBlur";
string window_name4 = "MedianBlur";
string window_name5 = "BilateralFilter"; 

int main( int argc, char** argv )
{
    if (argc < 2)
    {
	cerr << "Missing a file name\n"; 
    	return EXIT_FAILURE;
    }
    if (argc > 2)
    {
        cerr << "Too many arguments\n";
	return EXIT_FAILURE; 
    }

    int DIMENSION = 15; 
    /// Load the source image
    src = imread( argv[1], 1 );

	
    normalized = src.clone();
    gaussian = src.clone(); 
    median = src.clone(); 
    bilateral = src.clone(); 
    
    blur(src, normalized, Size(DIMENSION, DIMENSION), Point(-1,-1)); 
    GaussianBlur( src, gaussian, Size( DIMENSION, DIMENSION ), 0, 0 );
    medianBlur(src, median, DIMENSION); 	
    bilateralFilter(src, bilateral, DIMENSION, DIMENSION * 2, DIMENSION/2);		

    
    namedWindow( window_name1, WINDOW_AUTOSIZE );
    namedWindow( window_name2, WINDOW_AUTOSIZE );
    namedWindow( window_name3, WINDOW_AUTOSIZE );
    namedWindow( window_name4, WINDOW_AUTOSIZE );
    namedWindow( window_name5, WINDOW_AUTOSIZE );
    
    imshow(window_name1, src);
    imshow(window_name2, normalized);
    imshow(window_name3, gaussian);
    imshow(window_name4, median);
    imshow(window_name5, bilateral);

    imwrite("OutputFiles/Original.jpg", src); 	
    imwrite("OutputFiles/Normalized.jpg", normalized);
    imwrite("OutputFiles/Gaussian.jpg", gaussian);
    imwrite("OutputFiles/Median.jpg", median);
    imwrite("OutputFiles/Bilateral.jpg", bilateral);
	
    waitKey();
    return EXIT_SUCCESS;
}
