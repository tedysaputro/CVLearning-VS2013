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
	cvShowImage("Example in", image);
	
	// Create an image to hold the smoothed output
	/*
		we want to allocate our own image structure to which we can write our smoothed image. 
		The first argument is a CvSize structure, which we can conveniently create by calling cvGetSize(image);
		
		this gives us the size of the existing structure image. The second argument tells us what kind
		of data type is used for each channel on each pixel, and the last argument indicates the
		number of channels. So this image is three channels (with 8 bits per channel) and is the
		same size as image.
	*/
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
	cvShowImage("Example out", out);

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
	IplImage* img = cvLoadImage("D:\\yuki-kimoto.jpg");
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", img);
	example(img);
	//  cvWaitKey(0);
	cvReleaseImage(&img);
	cvDestroyWindow("Example1");
	return 0;
}

