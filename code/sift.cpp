#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <fstream>

using namespace cv;
using namespace std;
void main()
{

	// 新版本2.4.0方法
	initModule_nonfree();
	Mat img = imread("images\\features.jpg");
	ifstream fin("paras.txt");
	string line;
	vector<float>paras;
	getline(fin,line);
	cout<<line<<endl;
	int para_num=0;
	while(para_num<4){
		getline(fin,line);
		cout<<line<<endl;
		line.erase(0,line.find_first_of('=')+1);
		paras.push_back(atof(line.c_str()));
		++para_num;
	}
	Ptr<FeatureDetector> detector = FeatureDetector::create( "SIFT" );
	detector->set("nOctaveLayers",paras[0]);
	detector->set("contrastThreshold", paras[1]);
	detector->set("edgeThreshold",paras[2]);
	detector->set("sigma",paras[3]);
	vector<KeyPoint> keypoints;
	detector->detect( img, keypoints);

	//Draw And Match img1,img2 keypoints
	Mat img_keypoints;
	drawKeypoints(img,keypoints,img_keypoints,Scalar::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("SIFT",img_keypoints);
	imwrite("sift.png",img_keypoints);

	getline(fin,line);getline(fin,line);
	cout<<"\n"<<line<<endl;
	vector<int>surf_pars;
	while(getline(fin,line)){
		cout<<line<<endl;
		line.erase(0,line.find_first_of('=')+1);
		surf_pars.push_back(atoi(line.c_str()));
	}
	Ptr<FeatureDetector> detector_surf = FeatureDetector::create( "SURF" );
	detector_surf->set("hessianThreshold", surf_pars[0]);
	detector_surf->set("nOctaves",surf_pars[1]);
	detector_surf->set("nOctaveLayers",surf_pars[2]);
	//detector_surf->set("extended",false);
	//detector_surf->set("upright",true);
	vector<KeyPoint> keypoints2;
	detector_surf->detect( img, keypoints2);

	//Draw And Match img1,img2 keypoints
	Mat img_keypoints2;
	drawKeypoints(img,keypoints2,img_keypoints2,Scalar::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


	imshow("SURF",img_keypoints2);
	imwrite("surf.png",img_keypoints2);
	waitKey(100000);
}