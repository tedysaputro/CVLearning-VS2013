// 17 Object Finder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>
#include "colorhistogram.h"
#include "histogram.h"
#include "objectfinder.h"
using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("waves.jpg", 0);
	if (!image.data)
		return 0;
	namedWindow("Image");
	imshow("Image", image);

	Mat imageROI;
	imageROI = image(Rect(360, 55, 40, 50));
	namedWindow("Reference");
	imshow("Reference", imageROI);

	histogram1D h;
	MatND hist = h.getHistogram(imageROI);
	namedWindow("Reference Hist");
	imshow("Reference Hist", h.getHistogramImage(imageROI));

	ObjectFinder finder;
	finder.setHistogram(hist);
	finder.setThreshold(-1.0f);

	//get back-projection
	Mat result1;
	result1 = finder.find(image);

	// Create negative image and display result
	Mat tmp;
	result1.convertTo(tmp, CV_8U, -1.0, 255.0);
	namedWindow("Backprojection result");
	imshow("Backprojection result", tmp);

	// Get binary back-projection
	finder.setThreshold(0.12f);
	result1 = finder.find(image);

	// Draw a rectangle around the reference area
	rectangle(image, cv::Rect(360, 55, 40, 50), cv::Scalar(0, 0, 0));

	// Display image
	namedWindow("Image2");
	imshow("Image2", image);
	

	// Display result
	namedWindow("Detection Result");
	imshow("Detection Result", result1);



	// Load color image
	ColorHistogram hc;
	Mat color = cv::imread("waves.jpg");
	color = hc.colorReduce(color, 32);
	namedWindow("Color Image");
	imshow("Color Image", color);

	imageROI = color(cv::Rect(0, 0, 165, 75)); // blue sky area
	namedWindow("ROI Color");
	imshow("ROI Color", imageROI);

	// Get 3D color histogram
	MatND shist = hc.getHistogram(imageROI);
	// Histograms with SparseMat does not work with OpenCV2.1
	// cv::SparseMat shist= hc.getSparseHistogram(imageROI);

	finder.setHistogram(shist);
	finder.setThreshold(0.05f);

	// Get back-projection of color histogram
	result1 = finder.find(color);

	namedWindow("Color Backproject Result");
	imshow("Color Backproject Result", result1);


	// Second color image
	Mat color2 = imread("dog.jpg");
	color2 = hc.colorReduce(color2, 32);
	namedWindow("dog");
	imshow("dog", color2);
	// Get back-projection of color histogram
	Mat result2;
	result2 = finder.find(color2);

	namedWindow("Result color (2)");
	imshow("Result color (2)", result2);


	waitKey();
	return 0;
}

