#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

Mat src, src_gray,src_copy;
vector<Vec3f> circles;
char* window_name = "Hough Circle Transform Demo";
int hough_threshold=0;
int canny_threshold=300;

void HoughThreshold(int, void*)
{
	src.copyTo(src_copy);
	/// Convert it to gray
	cvtColor( src_copy, src_gray, CV_BGR2GRAY );

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

	/// Apply the Hough Transform to find the circles
	HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, hough_threshold+1, canny_threshold+10, 100, 0, 0 );
	/// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle( src_copy, center, 3, Scalar(255,0,0), -1, 8, 0 );
		// circle outline
		circle( src_copy, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}
	imshow(window_name,src_copy);
}


int main()
{
   
   /// Read the image
   src = imread( "images\\circle.jpg", 1 );

   if( !src.data )
     { return -1; }

   


   /// Show your results
	namedWindow( window_name, CV_WINDOW_AUTOSIZE );
	int max=src.rows/16;
	createTrackbar( "VoteThre", window_name, &hough_threshold,max, HoughThreshold );
	createTrackbar("CannyThre",window_name, &canny_threshold,300, HoughThreshold );
	imshow(window_name,src);
    waitKey(0);
    return 0;
}