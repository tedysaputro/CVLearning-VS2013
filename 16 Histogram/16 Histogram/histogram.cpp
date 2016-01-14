#include "stdafx.h"
#include "histogram.h"

#include <opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
histogram1D::histogram1D()
{
	//prepare arguments for 1D histogram
	histSize[0] = 256;
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	ranges[0] = hranges;
	channels[0] = 0;//by default we look at channel 0
}

void histogram1D::setChannel(int c){
	channels[0] = c;
}

int histogram1D::getChannel(){
	return channels[0];

}

void histogram1D::setRange(float minValue, float maxValue){
	hranges[0] = minValue;
	hranges[1] = maxValue;


}

float histogram1D::getMinValue(){
	return hranges[0];
}

float histogram1D::getMaxValue(){
	return hranges[1];
}

int histogram1D::getNBins(){
	return histSize[0];
}

MatND histogram1D::getHistogram(const Mat &image){
	MatND hist;

	//Compute histogram
	calcHist(&image,
		1,			//histogram of 1 image only
		channels,	//the channel used
		Mat(),		//no mask is used
		hist,		//the resulting histogram
		1,			//it is a 1D histogramm
		histSize,	//number of bins
		ranges		//pixe value range
		);
	return hist;
};

Mat histogram1D::getHistogramImage(const Mat &image){
	//compute histogram first
	MatND hist = getHistogram(image);

	//get min and max bin values
	double maxVal = 0;
	double minVal = 0;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);

	//image on which to display histogram
	Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));

	//set highest point at 90% of nbins
	int hpt = static_cast<int>(0.9*histSize[0]);

	//Draw vertical line for each bin
	for (int h = 0; h < histSize[0]; h++){
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*hpt / maxVal);
		line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
	}

	return histImg;
}
Mat histogram1D::equalize(const Mat &image){
	Mat result;
	equalizeHist(image, result);

	return result;
}

/*
One can therefore stretch the histogram in order to produce an image with an expanded contrast. 
The procedure is designed to detect the lowest (imin) and the highest (imax) intensity value with non-zero count in the
image histogram.
*/
Mat histogram1D::strecth(const Mat &image, int minValue = 0){
	//compute histogram first 
	MatND hist = getHistogram(image);

	// find left extremity of the histogram
	int imin = 0;
	for (; imin < histSize[0]; imin++){
		std::cout << hist.at<float>(imin) << std::endl;
		if (hist.at<float>(imin)>minValue)
			break;
	}

	//find right extremitiy of the histogram
	int imax = histSize[0] - 1;
	for (; imax >= 0; imax--){
		if (hist.at<float>(imax) > minValue)
			break;
	}
	//Create lookup table
	int dims[1] = { 256 };
	MatND lookup(1, dims, CV_8U);
	/*
		 The intensity values can then be remapped such that the imin value is
		repositioned at intensity 0, and the imax is assigned value 255. The in-between intensities i
		are simply linearly remapped as follows:
	*/
	for (int i = 0; i < 256; i++){
		if (i < imin) lookup.at<uchar>(i) = 0;
		else if (i>imax) lookup.at<uchar>(i) = 2;
		else lookup.at<uchar>(i) = static_cast<uchar>(255.0*(i - imin) / (imax - imin) + 0.5);
	}
	/*
		Note the call to our applyLookUp method once this one has been computed.
		Also, in practice, it could be advantageous to not only ignore bins with 0 value, but also entries with
		negligible count
	*/
	Mat result;
	result = applyLookUp(image, lookup);

	return result;
}
//Function cv::LUT in OpenCV applies a look-up table to an image in order to produce a new
//image.
Mat histogram1D::applyLookUp(const Mat& image, const MatND& lookup){
	// Set output image (always 1-channel)
	Mat result(image.rows, image.cols, CV_8U);
	Mat_<uchar>::iterator itr = result.begin<uchar>();

	//iterates over the input image
	Mat_<uchar>::const_iterator it = image.begin<uchar>();
	Mat_<uchar>::const_iterator itend = image.end<uchar>();

	//Applies lookup to each pixel
	for (; it != itend; ++it, ++itr){
		*itr = lookup.at<uchar>(*it);
	}
	return result;

}
