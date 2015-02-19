// 10 TrackBack and Pixel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <stdio.h>

//function declaration
void tbCallback(int _val, void* _data);

int _tmain(int argc, _TCHAR* argv[])
{
	//Crate a Mat Object and Read an image
	cv::Mat img;
	img = cv::imread("D://yuki.jpg", -1);

	cv::namedWindow("basic 2", cv::WINDOW_NORMAL);

	//create a trackback
	int tbVal = 30;
	int tbMaxVal = 60;
	void *pImg = &img;
	cv::createTrackbar("Tb1", "basic 2", &tbVal, tbMaxVal, tbCallback, pImg);

	//Display
	imshow("basic 2", img);

	//wait until a key is pressed
	cv::waitKey(0);
	return 0;
}

//@functiuon tbCallback
void tbCallback(int _val, void* _data){
	printf("--> trackbar is %d \n", _val);

	cv::Mat* pImg;
	pImg = static_cast<cv::Mat*>(_data);

	//Use the Trackbar value and _data to modify the image displayed
	cv::Mat img_modified;
	img_modified = *pImg + cv::Scalar(_val, _val, _val);
	
	//Display the modified image
	imshow("basic 2", img_modified);
}
