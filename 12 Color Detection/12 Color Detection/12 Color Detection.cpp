// 12 Color Detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	VideoCapture cap(0);
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;
		
		/*
			Usually, one can think that BGR color space is more suitable for color based segmentation. 
			But HSV color space is the most suitable color space for color based image segmentation. 
			
			So, in the above application, I have converted the color space of original image of the video from BGR to HSV image.
			HSV color space is also consists of 3 matrices, HUE, SATURATION and VALUE. 
			
			In OpenCV, value range for  HUE, SATURATION  and VALUE  are respectively 0-179, 0-255 and 0-255. 
			HUE represents the color, 
			SATURATION  represents the amount to which that respective color is mixed with white 
			and VALUE  represents the  amount to which that respective color is mixed with black.
　
			I have considered that the red object has HUE, SATURATION and VALUE in between 170-180, 160-255, 60-255 respectively. 
			
			Here the HUE is unique for that specific color distribution of that object. 
			
			But SATURATION and VALUE may be vary according to the lighting condition of that environment.

			Hue values of basic colors
			Orange  0-22
			Yellow 22- 38
			Green 38-75
			Blue 75-130
			Violet 130-160
			Red 160-179
			These are approximate values. You have to find the exact range of HUE values according to the color of the object. 
			
			I found that the range of 170-179 is perfect for the range of hue values of my object. 
			
			The SATURATION and VALUE is depend on the lighting condition of the environment as well as the surface of the object. 

		*/
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;
		/*
			void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst);
			
			Checks that each element of 'src'  lies between 'lowerb' and 'upperb'. 
			If so, that respective location of  'dst' is assigned '255' , otherwise '0'. 
			(Pixels with value 255 is shown as white whereas pixels with value 0 is shown as black)
		*/
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}

