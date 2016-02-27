#pragma once
#if !defined MORPHOF
#define MORPHOF
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

class MorphoFeatures
{
public:
	MorphoFeatures();
	void setThreshold(int t);
	int getThreshold() const;
	Mat getEdges(const Mat &image);
	Mat getCorners(const Mat &image);
	void drawOnImage(const Mat& binary, Mat&image);

private:
	//threshold to produce binary images
	int threshold;
	//structuring elements used in corner detection
	Mat cross;
	Mat diamond;
	Mat square;
	Mat x;

	void applyThreshold(Mat& result);


};

#endif