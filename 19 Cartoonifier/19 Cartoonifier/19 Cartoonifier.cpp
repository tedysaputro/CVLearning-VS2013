// 19 Cartoonifier.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\highgui\highgui.hpp"
#include <iostream>
#include "cartoon.h"

using namespace cv;
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame Size:" << dWidth << "x" << dHeight << endl;

	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Frame2", CV_WINDOW_AUTOSIZE);

	while (1)
	{
		Mat frame;
		bool bSuccess = cap.read(frame);
		if (!bSuccess)
		{
			cout << "Cannot read a frame video stream" << endl;
			break;
		}
		Mat frame2 = Mat(frame.size(), CV_8UC3);
		imshow("Original", frame);
		cartoon c;
		c.cartoonifyImage(frame, frame2);
		imshow("Frame2", frame2);


		if(waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}


	}
	return 0;
	return 0;
}

