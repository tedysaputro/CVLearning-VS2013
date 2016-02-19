#pragma once
#include "opencv2\opencv.hpp"
using namespace cv;
class cartoon
{
public:
	cartoon();
	~cartoon();
	void cartoonifyImage(Mat srcColor, Mat dst);
};

