#include "stdafx.h"
#include "objectfinder.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

ObjectFinder::ObjectFinder() : threshold(0.1f), isSparse(false) {

	ranges[0] = hranges; // all channels have the same range 
	ranges[1] = hranges;
	ranges[2] = hranges;
}
void ObjectFinder::setThreshold(float t){
	threshold = t;
}

float ObjectFinder::getThreshold(){
	return threshold;
}

void ObjectFinder::setHistogram(const MatND& h){
	isSparse = false;
	histogram = h;
	/*
	By normalizing this histogram, we obtain a function that gives the probability of a pixel of a
	given intensity value to belong to the defined area:
	*/
	normalize(histogram, histogram, 1.0);
}

void ObjectFinder::setHistogram(const SparseMat& h){
	isSparse = true;
	shistogram = h;

	
	normalize(shistogram, shistogram, 1.0, NORM_L2);
}

Mat ObjectFinder::find(const Mat& image){
	Mat result;

	hranges[0] = 0.0;	//range [0,255]
	hranges[1] = 255.0; 
	channels[0] = 0;	//the three channels
	channels[1] = 1;
	channels[2] = 2;
	if (isSparse){		//call the right function based on histogram type
		/*
			Backprojecting a histogram consists in replacing each pixel value 
			in an input image by its corresponding probability value read in the normalized histogram
		*/
		calcBackProject(&image,
			1,						//one image
			channels,				//vector specifying what histogram dimensions belong to what image channels 
			shistogram,				//the histogram we are using
			result,					//the resulting back projection image
			ranges,					//the range of values for each dimension
			255.0					//the scaling factor is chosen such that a histogram value of 1 maps to 255
			);
		
	}
	else{
		calcBackProject(&image,
			1,						//one image
			channels,				//vector specifying what histogram dimensions belong to what image channels
			histogram,				//the histogram we are using
			result,					//the resulting back projection image
			ranges,					// the range of values, for each dimension
			255.0					//// the scaling factor is chosen such that a histogram value of 1 maps to 255
			);
	}

	//threshold back projection to obtain a binary image
	if (threshold > 0.0)
		cv::threshold(result, result, 255 * threshold, 255, THRESH_BINARY);
	
	return result;
}

Mat ObjectFinder::find(const Mat& image, float minValue, float maxValue, int *channels, int dim){
	Mat result;
	hranges[0] = minValue;
	hranges[1] = maxValue;

	for (int i = 0; i < dim; i++)
		this->channels[i] = channels[i];

	if (isSparse){	// call the right function based on histogram type
		calcBackProject(&image,
			1,					// we only use one image at a time
			channels,			// vector specifying what histogram dimensions belong to what image channels
			shistogram,			// the histogram we are using
			result,				// the resulting back projection image
			ranges,				// the range of values, for each dimension
			255.0				// the scaling factor is chosen such that a histogram value of 1 maps to 255
			);
	}
	else{
		calcBackProject(&image,
			1,
			channels,
			histogram,
			result,
			ranges,
			255.0

			);

	}

	//Threshold back projection to obtain a binary image
	if (threshold > 0.0)
		cv::threshold(result, result, 255 * threshold, 255, THRESH_BINARY);

	return result;
}