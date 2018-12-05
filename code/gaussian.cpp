////**
//// * file Smoothing.cpp
//// * brief Sample code for simple filters
//// * author OpenCV team
//// */
#include <iostream>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace std;
using namespace cv;

/// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;

int main( int argc, char** argv )
{

	/// Load the source image
	src = imread( "images/scale_0.jpg", 1 ); 
	imshow("scale_0",src);
	dst = src.clone();
	//for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
	//{ GaussianBlur( src, dst, Size( i, i ), 0, 0 );

	GaussianBlur( src, dst, Size( 1, 1 ), 0, 0 );
	imshow("scale_1",dst);
	imwrite("images/scale_1.png",dst);

	GaussianBlur( src, dst, Size( 9, 9 ), 0, 0 );
	imshow("scale_8",dst);
	imwrite("images/scale_8.png",dst);

	GaussianBlur( src, dst, Size( 65, 65 ), 0, 0 );
	imshow("scale_64",dst);
	imwrite("images/scale_64.png",dst);


	
	waitKey(0);

	return 0;
}
