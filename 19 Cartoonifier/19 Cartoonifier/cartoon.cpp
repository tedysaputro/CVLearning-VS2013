#include "stdafx.h"
#include "cartoon.h"


cartoon::cartoon()
{
}

void cartoon::cartoonifyImage(Mat srcColor, Mat dst){
	Mat srcGray;
	cvtColor(srcColor, srcGray, CV_BGR2GRAY);
	medianBlur(srcColor, srcGray, 7);
	Size size = srcColor.size();
	Mat mask = Mat(size, CV_8U);
	Mat edges = Mat(size, CV_8U);
	Laplacian(srcGray, edges, CV_8U, 5);
	threshold(edges, mask, 80, 255, THRESH_BINARY_INV);
	//imshow("edges", edges);
	//imshow("mask", mask);

	//cvtColor(mask, dst, CV_GRAY2BGR);
	Size smallSize;
	smallSize.width = size.width / 2;
	smallSize.height = size.height / 2;
	Mat smallImg = Mat(smallSize, CV_8UC3);
	resize(srcColor, smallImg, smallSize, 0, 0, INTER_LINEAR);

	// Perform many iterations of weak bilateral filtering, to enhance the edges
	// while blurring the flat regions, like a cartoon.
	Mat tmp = Mat(smallSize, CV_8UC3);
	int repetitions = 7;        // Repetitions for strong cartoon effect.
	for (int i = 0; i<repetitions; i++) {
		int size = 9;           // Filter size. Has a large effect on speed.
		double sigmaColor = 9;  // Filter color strength.
		double sigmaSpace = 7;  // Positional strength. Effects speed.
		bilateralFilter(smallImg, tmp, size, sigmaColor, sigmaSpace);
		bilateralFilter(tmp, smallImg, size, sigmaColor, sigmaSpace);
	}
	// Go back to the original scale.
	resize(smallImg, srcColor, size, 0, 0, INTER_LINEAR);

	// Clear the output image to black, so that the cartoon line drawings will be black (ie: not drawn).
	memset((char*)dst.data, 0, dst.step * dst.rows);

	// Use the blurry cartoon image, except for the strong edges that we will leave black.
	srcColor.copyTo(dst, mask);
}

cartoon::~cartoon()
{
}
