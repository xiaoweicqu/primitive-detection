#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace cv;

void main()
{
	Mat image = imread("images\\features.jpg");
	Mat descriptors;
	vector<KeyPoint> keypoints;
	// 新版本2.4.0方法
	//initModule_nonfree();

	//Ptr<FeatureDetector> detector = FeatureDetector::create( "GFTT" );
	// detector->detect( image, keypoints );  

	// 2.3.1方法
	// 	SiftFeatureDetector sift2(0.06f, 10.0);
	// 	sift2.detect(imageGray, keypoints);

	SimpleBlobDetector::Params params;
	//params.minThreshold = 10;
	//params.maxThreshold = 100;
	//params.thresholdStep = 10;

	//params.minArea = 10; 
	//params.minConvexity = 0.3;
	//params.minInertiaRatio = 0.01;

	//params.maxArea = 8000;
	//params.maxConvexity = 10;

	//params.filterByColor = false;
	//params.filterByCircularity = false;


	SimpleBlobDetector blobDetector( params );
	blobDetector.create("SimpleBlob");
	blobDetector.detect( image, keypoints );

	drawKeypoints(image, keypoints, image, Scalar(255,0,0));

	imshow("Blob", image);
	imwrite("images\\features_blob.png",image);
	waitKey();
}
