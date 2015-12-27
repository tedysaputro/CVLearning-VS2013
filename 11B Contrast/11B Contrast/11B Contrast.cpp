// 11B Contrast.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2\highgui\highgui.hpp"
using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat img = imread("D:\\yuki-kimoto.jpg", CV_LOAD_IMAGE_COLOR);
	if (img.empty()){
		cout << "Image cannot be loaded" << endl;

	}

	Mat imgH;
	/*
	void convertTo( OutputArray m, int rtype, double alpha=1, double beta=0 )
	This OpenCV function converts  image into another format with scaling. Scaling is done according to the following formula.
	m[i,j] = alfa * img[i,j] + beta

	Here is the parameters of this function
	OutputArray m - Store the converted image
	int rtype - Depth of the output image. If the value of rtype is negative, output type is same as the input image. I have used a negative value in the above program because I don't want to change the depth of the original image. Possible inputs to this parameter
	CV_8U
	CV_32S
	CV_64F
	-1
	Complete list of depths can be found in Basics of OpenCV API

	double alpha - Multiplication factor; Every pixel will be multiplied by this value
	double beta - This value will be added to very pixels after multiplying with the above value.
	Here is the formula again. Here m[i, j] means a pixel at ith row and jth column.
	m[i,j] = alfa * img[i,j] + beta


	*/
	img.convertTo(imgH, -1, 2, 0);//increase the contrast (double)

	Mat imgL;
	img.convertTo(imgL, -1, 0.5, 0);//decrease the contrast (halve)

	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("High Contrast", CV_WINDOW_AUTOSIZE);
	namedWindow("Low Contrast", CV_WINDOW_AUTOSIZE);

	imshow("Original Image", img);
	imshow("High Contrast", imgH);
	imshow("Low Contrast", imgL);

	waitKey(0);
	destroyAllWindows();

	return 0;
}

