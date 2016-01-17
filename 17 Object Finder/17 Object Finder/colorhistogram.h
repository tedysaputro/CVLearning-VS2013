#pragma once
#if !defined COLHISTOGRAM
#define COLHISTOGRAM

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
class ColorHistogram
{
private:
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];
public:
	ColorHistogram();
	//computes the histogram
	MatND getHistogram(const Mat &image);
	//computes the histogram
	SparseMat getSparseHistogram(const Mat &image);
	//computes the 2D ab histogram
	//BGR source image is converted to Lab
	MatND getabHistogram(const Mat &image);
	//computes the 1D hue histogram with a mask
	// BGR source image is converted to HSV
	MatND getHueHistogram(const Mat &image);

	Mat colorReduce(const Mat &image, int div);

};
#endif

