// 18 MeanShiftAlghoritm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\tracking.hpp>

#include "objectfinder.h"
#include "colorhistogram.h"

using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("baboon1.jpg");
	if (!image.data)
		return 0;
	Mat imageROI = image(Rect(110, 260, 35, 40));
	rectangle(image, Rect(110, 260, 35, 40), Scalar(0, 0, 255));
	namedWindow("Image");
	imshow("Image", image);

	//get the hue histogram
	int minSat = 65;
	ColorHistogram hc;
	MatND colorhist = hc.getHueHistogram(imageROI,minSat);

	ObjectFinder finder;
	finder.setHistogram(colorhist);
	finder.setThreshold(0.2f);

	//convert to HSV space

	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);

	//split the image
	vector<Mat> v;
	split(hsv, v);

	// Eliminate pixels with low saturation
	threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
	namedWindow("Saturation");
	imshow("Saturation", v[1]);

	// Get back-projection of hue histogram
	int ch[1] = { 0 };
	Mat result = finder.find(hsv, 0.0f, 180.0f, ch, 1);

	namedWindow("Result Hue");
	imshow("Result Hue", result);

	bitwise_and(result, v[1], result);
	namedWindow("Result Hue and");
	imshow("Result Hue and", result);



	// Second image
	image = imread("baboon3.jpg");

	// Display image
	namedWindow("Image 2");
	imshow("Image 2", image);

	// Convert to HSV space
	cvtColor(image, hsv, CV_BGR2HSV);

	// Split the image
	split(hsv, v);

	// Eliminate pixels with low saturation
	threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
	namedWindow("Saturation");
	imshow("Saturation", v[1]);

	// Get back-projection of hue histogram
	result = finder.find(hsv, 0.0f, 180.0f, ch, 1);

	namedWindow("Result Hue");
	imshow("Result Hue", result);

	// Eliminate low stauration pixels
	bitwise_and(result, v[1], result);
	namedWindow("Result Hue and");
	imshow("Result Hue and", result);

	// Get back-projection of hue histogram
	finder.setThreshold(-1.0f);
	result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
	bitwise_and(result, v[1], result);
	namedWindow("Result Hue and raw");
	imshow("Result Hue and raw", result);

	Rect rect(110, 260, 35, 40);
	rectangle(image, rect, Scalar(0, 0, 255));

	TermCriteria criteria(TermCriteria::MAX_ITER, 10, 0.01);
	cout << "meanshift= " << cv::meanShift(result, rect, criteria) << endl;

	rectangle(image, rect, Scalar(0, 255, 0));

	// Display image
	namedWindow("Image 2 result");
	imshow("Image 2 result", image);

	waitKey();
	return 0;
}

