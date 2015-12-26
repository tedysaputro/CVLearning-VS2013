// 11A Change Brightness.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\highgui\highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat img = imread("D:\\yuki-kimoto.jpg", CV_LOAD_IMAGE_COLOR);
	if (img.empty()){
		cout << "image cannot be loaded" << endl;
		return -1;
	}

	Mat imgH = img + Scalar(75, 75, 75);//increase the brightness by 75
	Mat imgL = img + Scalar(-75, -75, -75);
	
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("High Brightness", CV_WINDOW_AUTOSIZE);
	namedWindow("Low Brightness", CV_WINDOW_AUTOSIZE);

	imshow("Original Image", img);
	imshow("High Brightness", imgH);
	imshow("Low Brightness", imgL);

	waitKey(0);
	destroyAllWindows();



	return 0;
}

