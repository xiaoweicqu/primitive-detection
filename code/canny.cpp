#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;
int edgeThresh = 1;
int lowThreshold,maxThreshold;
int kernel_size = 3;
char* window_name = "Canny Demo";

void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, maxThreshold, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

void CannyThreshold2(int, void*)
{
	/// Reduce noise with a kernel 3x3
	blur( src_gray, detected_edges, Size(3,3) );
	/// Canny detector
	Canny( detected_edges, detected_edges, lowThreshold, maxThreshold, kernel_size );
	dst = Scalar::all(0);
	src.copyTo( dst, detected_edges);
	imshow( window_name, dst );
}

int main( )
{
	lowThreshold=maxThreshold=0;
  src = imread( "images\\Lena.jpg" );
  if( !src.data )
    { return -1; }
  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, CV_BGR2GRAY );
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
  createTrackbar( "Min Thresh", window_name, &lowThreshold, 100, CannyThreshold );
  createTrackbar( "Max Thresh", window_name, &maxThreshold, 200, CannyThreshold2 );
  CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}
