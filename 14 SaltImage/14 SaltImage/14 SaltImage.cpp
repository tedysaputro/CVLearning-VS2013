// 14 SaltImage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;

//some pixels are replaced by a white or a black pixel
//The function is made of a single loop that assigns n times the value 255 to randomly selected
//pixels.
void salt(Mat &image, int n){
	//the pixel column i and row j are selected using a random number generator.
	int i, j;
	for (int k = 0; k < n; k++){

		i = rand() % image.cols;//The public member variables cols and rows give you the number of columns and rows in the image.
		j = rand() % image.rows;
		//distinguish the two cases of gray-level and color images by checking the number
		//of channels associated with each pixel.In the case of a gray - level image, the number 255
		//	is assigned to the single 8 - bit value.For a color image, you need to assign 255 to the three
		//	primary color channels in order to obtain a white pixel.
		if (image.channels() == 1){
			// For element access, cv::Mat has the method at(int y, int x). However, the
			// type returned by a method must be known at compile time, and since a cv::Mat can hold
			//	elements of any type, the programmer needs to specify the return type that is expected.This
			//	is why the at method has been implemented as a template method.
			image.at<uchar>(j, i) = 255;


		}
		else if (image.channels() == 3){
			//In color images, each pixel is associated with three components: the red, green, and blue
			//channels.Therefore, a cv::Mat containing a color image will return a vector of three 8 - bit
			//	values.OpenCV has a defined type for such short vectors that is called cv::Vec3b.It is a
			//	vector of 3 unsigned chars.This explains why the element access to the pixels of a color
			//	pixel is written as :
			image.at<Vec3b>(j, i)[0] = 255;
			image.at<Vec3b>(j, i)[1] = 255;
			image.at<Vec3b>(j, i)[2] = 255;

		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	srand(getTickCount());
	Mat image = imread("D:\\yuki-kimoto.jpg");
	salt(image, 3000);
	namedWindow("Image");
	imshow("Image", image);
//	imwrite("salted.bmp", image);
	waitKey(5000);
	return 0;
}

