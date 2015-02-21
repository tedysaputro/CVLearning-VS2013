// 11 FilteringImages.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	IplImage*img = cvLoadImage("D://yuki-kimoto-012.jpg");
	cvNamedWindow("My Window");
	cvShowImage("My Window", img);
	

	cvNot(img, img);
	cvNamedWindow("inverted");
	cvShowImage("inverted", img);

	//dilate and display the dilated image
	//cvDilate(img, img, 0, 2);
	//cvNamedWindow("Dilated");
	//cvShowImage("Dilated", img);

	

	cvWaitKey(0);

	//cleaning up
	cvDestroyWindow("My Window");
	cvDestroyWindow("inverted");
	//cvDestroyWindow("Dilated");
	cvReleaseImage(&img);
	return 0;
}

