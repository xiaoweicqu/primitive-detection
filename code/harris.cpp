/**
 * @function cornerDemo.cpp
 * @brief Demo code for detecting corners using Harris-Stephens method and Shi-Tomasi method
 * @author Wei Lan http://blog.csdn.net/xiaowei_cqu
 */
#include <stdio.h> 
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <vector> 
using namespace cv;
using namespace std;

 //Global variables
Mat src, src_gray,dst_norm_scaled,src_copy;
int thresh = 0;
int max_thresh = 100;

int maxCorners = 0;
int maxTrackbar = 50;

char* source_window = "Source image";
char* corners_window = "Corners detected";

/// Function header
void cornerHarris_demo( int, void* );
//void cornerShiTomasi_demo( int, void* );

int main( )
{
  src =  imread("images\\corner.png",1);
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window and a trackbar
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  createTrackbar( "Harris", source_window, &thresh, max_thresh, cornerHarris_demo );
  createTrackbar( "ShiTomasi", source_window, &maxCorners, maxTrackbar, cornerHarris_demo );  

  namedWindow( corners_window, CV_WINDOW_AUTOSIZE );
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );

  cornerHarris_demo( 0, 0 );
  //cornerShiTomasi_demo( 0, 0 );


  waitKey(0);
  return(0);
}

void cornerHarris_demo( int, void* )
{
	src.copyTo(src_copy);
  Mat dst, dst_norm;
  dst = Mat::zeros( src.size(), CV_32FC1 );
  /// Detector parameters
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;
  /// Detecting corners
  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
  /// Normalizing
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled ); 
  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh+60 )
              { 
				circle( dst_norm_scaled, Point( i, j ), 6,  Scalar(0), -1, 8, 0 ); 
				circle(src_copy,Point( i, j ), 5,  Scalar(255,0,0), -1, 8, 0 );
              }
          } 
     }    

  if( maxCorners < 1 ) { maxCorners = 1; }
  /// Parameters for Shi-Tomasi algorithm
  vector<Point2f> corners;
  double qualityLevel = 0.01;
  double minDistance = 10;
  bool useHarrisDetector = false;
  /// Copy the source image
  Mat cormat;
  /// Apply corner detection :Determines strong corners on an image.
  goodFeaturesToTrack( src_gray, 
	  corners,
	  maxCorners,
	  qualityLevel,
	  minDistance,
	  Mat(),
	  blockSize,
	  useHarrisDetector,
	  k );
  /// Draw corners detected
  for( int i = 0; i < corners.size(); i++ ){	
	  circle( dst_norm_scaled,  corners[i], 6,  Scalar(255), 2, 8, 0 ); 
	  circle( src_copy, corners[i], 4, Scalar(0,255,0), 2, 8, 0 ); 
  }

  imshow( corners_window, dst_norm_scaled );
  imshow( source_window, src_copy );  



}