#include "stdafx.h"
#include "colorhistogram.h"

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
ColorHistogram::ColorHistogram()
{
	//prepare arguments for a color histogram
	histSize[0] = histSize[1] = histSize[2] = 256;
	hranges[0] = 0.0;//BRG range
	hranges[1] = 255.0;
	ranges[0] = hranges;//all channels have the same range
	ranges[1] = hranges;
	ranges[2] = hranges;
	channels[0] = 0;
	channels[1] = 1;
	channels[2] = 2;


}

MatND ColorHistogram::getHistogram(const Mat &image){
	MatND hist;

	//BGR color histogram
	hranges[0] = 0.0;//BRG range
	hranges[1] = 255.0;
	channels[0] = 0;//the three channles
	channels[1] = 1;
	channels[2] = 2;

	//compute histogram
	calcHist(&image,
		1,			//histogram of 1 image only
		channels,	//the channel used
		Mat(),			//no mask used
		hist,		//the resulting histogram
		3,			//it is a 3D histogram
		histSize,	//number of bins
		ranges		//pixel value range
		);
	return hist;

}

SparseMat ColorHistogram::getSparseHistogram(const cv::Mat &image){
	SparseMat hist(3, histSize, CV_32F);
	//BGR color histogram
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	channels[0] = 0;//the three channels 
	channels[1] = 1;
	channels[2] = 2;

	//compute histogram
	calcHist(&image,
		1,			//histogram of 1 image only
		channels,	//the channel used
		Mat(),		//no mask is used
		hist,		//the resulting histogram
		3,			//it is a 3D histogram
		histSize,	//number of bins
		ranges		//pixel value range
		);

	return hist;

}
//computes the 2D ab histogram
MatND ColorHistogram::getabHistogram(const Mat &image){
	MatND hist;

	//convert to Lab color space
	Mat lab;
	cvtColor(image, lab, CV_BGR2Lab);

	//prepare arguments for 2D color histogram
	hranges[0] = -128.0;
	hranges[1] = 127.0;
	channels[0] = 1;
	channels[1] = 2;

	//compute histogram
	calcHist(&lab,
		1,			//histogram of 1 image only
		channels,	//the channel used
		Mat(),		//no mask is used
		hist,		// the resulting histogram
		2,			//it is a 2D histogram
		histSize,	//number of bins
		ranges		//pixel value range
		);
	return hist;
}

//computes the 1D hue histogram with a mask
//BGR source image is converted to HSV
MatND ColorHistogram::getHueHistogram(const Mat &image){
	MatND hist;

	//convert to lab color space
	Mat hue;
	cvtColor(image, hue, CV_BGR2HSV);
	
	//prepare arguments for a 1D hue histogram
	hranges[0] = 0.0;
	hranges[1] = 180.0;
	channels[0] = 0;//the hue channel

	//compute histogram
	calcHist(&hue,
		1,			//histogram of 1 image only
		channels,	//the channel used
		Mat(),		//no mask is used
		hist,		//the resulting histogramm
		1,			//it is a 1D histogram
		histSize,	//number of bins
		ranges		//pixel value range
		);

	return hist;



}

Mat ColorHistogram::colorReduce(const Mat &image, int div = 64){
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	//mask used to round the pixel value
	uchar mask = 0xFF << n;//eg for div =16, mask=0xF0;
	Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();

	//set output image (always 1 -channel)
	Mat result(image.rows, image.cols, image.type());
	Mat_<Vec3b>::iterator itr = result.begin<Vec3b>();
	for (; it != itend; ++it, ++itr){
		(*itr)[0] = ((*it)[0] &mask) + div / 2;
		(*itr)[1] = ((*it)[1] &mask) + div / 2;
		(*itr)[2] = ((*it)[2] &mask) + div / 2;

	}
	return result;

}

