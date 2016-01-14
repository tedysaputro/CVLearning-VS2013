// 16 Histogram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "opencv\cv.h"
#include "opencv2\highgui\highgui.hpp"
#include "histogram.h"

using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{

	Mat image = imread("D:\\group.jpg", 0);
	if (!image.data)
		return 0;

	//Display the image
	namedWindow("image");
	imshow("image", image);


	//the histogram object
	histogram1D h;

	//compute the histogram
	//The histo object here is a simple one-dimensional array with 256 entries
	MatND histo = h.getHistogram(image);

	//loop over each bin
	//Therefore, you can
	//read each bin by simply looping over this array:
	for (int i = 0; i < 256; i++)
		cout << "Value" << i << "=" << histo.at<float>(i) << endl;

	//display a histogram as an image

	namedWindow("Histogram");
	imshow("Histogram", h.getHistogramImage(image));

	// creating a binary image by thresholding at the valley
	Mat thresholded;
	threshold(image, thresholded, 60, 255, THRESH_BINARY);

	//display the thresholded image
	namedWindow("binary image");
	imshow("binary image", thresholded);
	/*
		in many cases, the visual deficiency of an image is not that it uses too narrow a range of intensities. 
		Rather, it is that some intensity values are used more frequently than others. The histogram shown in the
		earlier is a good example of this phenomenon. The middle-gray intensities are indeed heavily represented, 
		while darker and brighter pixel values are rather rare. In fact, one can think that a good-quality image 
		should make equal use of all available pixel intensities. This is the idea behind the concept of histogram equalization,
		that is making the image histogram as flat as possible.
	*/
	//equalize the image
	Mat eq = h.equalize(image);

	//show the result
	namedWindow("Equalized Image");
	imshow("Equalized Image", eq);

	//show the new histogram
	namedWindow("Equalized Histogram");
	imshow("Equalized Histogram", h.getHistogramImage(eq));

	//create ann inversion table
	int dim(256);

	Mat lookup(1,
		&dim,
		CV_8U);
	for (int i = 0; i < 256; i++){
		lookup.at<uchar>(i) = 255 - i;

	}
	//apply lookup and display negative image
	namedWindow("negative image");
	imshow("negative image", h.applyLookUp(image, lookup));
	
	waitKey();
	return 0;

}

