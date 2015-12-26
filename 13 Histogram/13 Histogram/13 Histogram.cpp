// 13 Histogram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void showHistogram(Mat& img)
{
	int bins = 256;//number of bins
	int nc = img.channels();//number of channels
	vector<Mat> hist(nc); //array for storing the histograms


	//initialize histogram arrays
	for (int i = 0; i < hist.size(); i++)
		hist[i] = Mat::zeros(1, bins, CV_32SC1);

	//calculate the histogram of the image
	/*
		We created the histogram arrays with CV_32S (alias for 4-bytes integer). 
		Using CV_32S, we can store values up to 2147483647. 
		This will make sure that the histogram arrays will not overflow for large input image.
	*/
	for (int i = 0; i < img.rows; i++){

	}

	vector<Mat> canvas(nc);//images for displaying the histogram
	int hmax[3] = { 0, 0, 0 };//peak valie for each histogram

}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

