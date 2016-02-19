// 12A Ball Tracking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	VideoCapture cap;
	cap.open("http://10.10.1.1:8196/?dummy=param.mjpg");
	if (!cap.isOpened()){

		cout << "cannot open the web cam" << endl;
		return -1;
	}
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int iLowH = 0;
	int iHighH = 64;

	int iLowS = 126;
	int iHighS = 238;

	int iLowV = 7;
	int iHighV = 255;

	//create trackbars in "Control" Window
	createTrackbar("LowH", "Control", &iLowH, 179);
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255);
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);
	createTrackbar("HighV", "Control", &iHighV, 255);

	int iLastX = -1;
	int iLastY = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal);// read a new frame from video
		int x = imgOriginal.cols / 2;
		int y = imgOriginal.rows / 2;
		int w = 100;
		int h = 500;
		int left_side = x - w / 2;
		int right_side = left_side+w;
		rectangle(imgOriginal, Rect(left_side, y - h / 2, w, h), Scalar(0, 255, 0));

		if (!bSuccess)//if not success, break loop
		{
			cout << "Cannot read a frame vido stream" << endl;
			break;
		}

		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);//Convert the captured frame from BGR to HSV

		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);//threshold the image
		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//calculate the moments of thresholded image
		Moments oMoments = moments(imgThresholded);
		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		//if the area<=1000, i consider that the are no object in the image and its because of the noise
		if (dArea >500000){
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;
//			if (iLastX >= 0 && iLastY >= 0 && posX > 0 && posY >= 0)
//			{
//				line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0, 0, 255), 2);
				//cout << "X="<<posX<<" Y="<<posY << endl;

				
//			}
			if (posX > left_side && posX<right_side){//di dalam kotak
				cout << left_side << ">" << posX << ">" << right_side<<endl;
			
			}
			else if (posX < left_side){
				cout << left_side << "<" << posX << " sebelah kiri target" << endl;
			}
			else if (posX > right_side){
				cout << right_side << ">" << posX << " sebelah kanan target" << endl;

			}
		
			iLastX = posX;
			iLastY = posY;

		}

		imshow("Thresholded Image", imgThresholded);//show the thresholded image
		imgOriginal = imgOriginal + imgLines;
		imshow("Original", imgOriginal);//show the original image
		if (waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}

