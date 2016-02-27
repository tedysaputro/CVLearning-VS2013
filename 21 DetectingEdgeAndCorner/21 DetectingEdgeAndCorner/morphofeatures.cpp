#include "stdafx.h"
#include "morphofeatures.h"

using namespace cv;
MorphoFeatures::MorphoFeatures():threshold(-1), cross(5, 5, CV_8U, cv::Scalar(0)),
								diamond(5, 5, CV_8U, cv::Scalar(1)),
								square(5, 5, CV_8U, cv::Scalar(1)),
								x(5, 5, CV_8U, cv::Scalar(0))

{
	//Creating the cross-shaped structuring elements
	for (int i = 0; i < 5; i++){
		cross.at<uchar>(2, i) = 1;
		cross.at<uchar>(i, 2) = 1;

	}

	//creating the diamond shaped structuring elements
	diamond.at<uchar>(0, 0) = 0;
	diamond.at<uchar>(0, 1) = 0;
	diamond.at<uchar>(1, 0) = 0;
	diamond.at<uchar>(4, 4) = 0;
	diamond.at<uchar>(4, 1) = 0;
	diamond.at<uchar>(3, 0) = 0;
	diamond.at<uchar>(0, 4) = 0;
	diamond.at<uchar>(0, 3) = 0;
	diamond.at<uchar>(1, 4) = 0;
	//creating the x-shaped structuring element
	for (int i = 0; i < 5; i++){
		x.at<uchar>(i, i) = 1;
		x.at<uchar>(4 - i, i) = 1;
	}
	

}


void MorphoFeatures::setThreshold(int t){
	threshold = t;
}

int MorphoFeatures::getThreshold() const{
	return threshold;
}



void MorphoFeatures::applyThreshold(Mat& result){
	//Apply threshold on result
	if (threshold > 0)
		cv::threshold(result, result, threshold, 255, THRESH_BINARY_INV);
}

Mat MorphoFeatures::getEdges(const Mat &image){
	//get the gradient image
	Mat result;
	morphologyEx(image, result, MORPH_GRADIENT, Mat());
	//apply threshold to obtain a binary image
	applyThreshold(result);

	return result;
}

Mat MorphoFeatures::getCorners(const Mat &image){

	Mat result;

	//Dilate with a cross
	dilate(image, result, cross);
	
	//Erode with a diamond
	erode(result, result, diamond);

	Mat result2;
	//dilate with aX
	dilate(image, result2, x);

	//erode with a square
	erode(result2, result2, square);

	//corners are obtained by differencing 
	//the two closed images
	absdiff(result2, result, result);

	// Apply threshold to obtain a binary image
	applyThreshold(result);

	return result;
}

void MorphoFeatures::drawOnImage(const Mat& binary, Mat& image){
	Mat_<uchar>::const_iterator it = binary.begin<uchar>();
	Mat_<uchar>::const_iterator itend = binary.end<uchar>();

	//for each pixel
	for (int i = 0; it != itend; ++it, ++i){
		if (!*it)
			circle(image, Point(i%image.step, i / image.step), 5, Scalar(255, 0, 0));
	}
}