// 04 A Simple Transformation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"

void example(IplImage* image){
	// Create some windows to show the input
	// and output images in.
	//
	cvNamedWindow("Example in", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example out", CV_WINDOW_AUTOSIZE);

	// Create a window to show our input image
	cvShowImage("Example in ", image);
	
	// Create an image to hold the smoothed output
	//
	IplImage* out = cvCreateImage(
		cvGetSize(image),
		IPL_DEPTH_8U,
		3
		);
	// Do the smoothing
	//
	cvSmooth(image, out, CV_GAUSSIAN, 5, 5);
	cvSmooth(out, out, CV_GAUSSIAN, 5, 5);

	// Show the smoothed image in the output window
	//
	cvShowImage("Example-out", out);

	// Be tidy
	//
	cvReleaseImage(&out);

	// Wait for the user to hit a key, then clean up the windows
	//
	cvWaitKey(0);
	cvDestroyWindow("Example-in");
	cvDestroyWindow("Example-out");
}


int _tmain(int argc, _TCHAR* argv[])
{
	IplImage* img = cvLoadImage("D:\\yuki.jpg");
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", img);
	example(img);
	//  cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Example1");
	return 0;
}

