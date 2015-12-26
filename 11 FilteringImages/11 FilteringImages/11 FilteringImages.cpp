// 11 FilteringImages.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	IplImage* img = cvLoadImage("D://yuki-kimoto.jpg");
	IplImage* imgNot = cvCreateImage(
		cvGetSize(img),
		IPL_DEPTH_8U,
		3
		);
	IplImage* imgDilate = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvNamedWindow("My Window");
	cvShowImage("My Window", img);
	

	cvNot(img, imgNot);
	cvNamedWindow("inverted");
	cvShowImage("inverted", imgNot);

	//dilate and display the dilated image
	
	cvDilate(img, imgDilate, 0, 2);
	cvNamedWindow("Dilated");
	cvShowImage("Dilated", imgDilate);

	

	cvWaitKey(0);

	//cleaning up
	cvDestroyWindow("My Window");
	cvDestroyWindow("inverted");
	cvDestroyWindow("Dilated");
	cvReleaseImage(&img);
	cvReleaseImage(&imgDilate);
	cvReleaseImage(&img);

	return 0;
}

