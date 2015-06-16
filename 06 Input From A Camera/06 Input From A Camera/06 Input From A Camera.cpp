// 06 Input From A Camera.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\opencv.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	cvNamedWindow("Example2_9", CV_WINDOW_AUTOSIZE);
	CvCapture* capture;
	
	capture = cvCreateCameraCapture(0);

	assert(capture != NULL);

	IplImage* frame;
	while (1) {
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage("Example2_9", frame);
		char c = cvWaitKey(10);
		if (c == 27) break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example2_9");
	return 0;
}

