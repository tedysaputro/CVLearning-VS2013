// 09 Matrix and Images.cpp : Defines the entry point for the console application.
// tedy

#include "stdafx.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	//create a matrix initialized to zeros (black)
	//note that we use zeros in a similar fashion as MatLab 
	//to initialize the 3-channel matrix with zeros (black)
	cv::Mat m = cv::Mat::zeros(300, 400, CV_8UC3);

	//set some matrix elements to green
	/*
		We created a header (roi_green) referencing to the region of interest
		defined by the rectangle cv::Rect(100, 75, 200, 150)

		in the matrix m (more details check Mat::operator()). The arguments indicate that the rectangle left-upper corner is (100,75) and the last two arguments indicate its dimensions.

		Any change in roi_green is equivalent to a change in the matrix m. 
		Notice that in the second line we set roi_green to color green 
		( B = 0, G = 255, R = 0 ), 
		
		so the pixels referenced in m will change values.
	*/
	cv::Mat roi_green(m, cv::Rect(100, 75, 200, 150));
	roi_green = cv::Scalar(0, 255, 0);

	//Set some matrix elements to red
	cv::Mat roi_red(m, cv::Rect(150, 100, 100, 100));
	roi_red = cv::Scalar(0, 0, 255);

	//created a named window
	cv::namedWindow("Test", cv::WINDOW_AUTOSIZE);

	//Display
	imshow("Test", m);

	//Wait until a key pressed
	cv::waitKey(0);

	return 0;
}

