// 15 Color Reduce.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>


using namespace cv;
// to reduce the complexity of an analysis, it is sometimes
//useful to reduce the number of colors in an image.
//One simple way to achieve this goal is
//to simply subdivide the RGB space into cubes of equal sizes
void colorReduce0(Mat &image, int div = 64){
	int nl = image.rows;//number of lines

	//total number of elements per line
	//number of pixel values per rows
	int nc = image.cols*image.channels();

	for (int j = 0; j < nl; j++){
		//get the address of row j

		//To simplify the computation of the pointer arithmetic, 
		//the cv::Mat class offers a method which directly gives 
		//you the address of an image row.
		//This is the ptr method.It is a template
		//	method that returns the address of row number j :
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++){
			//process each pixel-------
			/*
			 If N is the reduction factor, then for each pixel in the image and for each channel of this pixel, divide the value by N
			 (integer division, therefore the reminder is lost). Then multiply the result by N, this will give you the
			 multiple of N just below the input pixel value. Just add N/2 and you obtain the central position
			 of the interval between two adjacent multiples of N. 
			 
			 If you repeat this process for each 8-bit
			 channel value, then you will obtain a total of 256/N x 256/N x 256/N possible color values.
			*/
			data[i] = data[i] / div*div + div / 2;
			//end of pixel processing ------------
		}
	}

}



void colorReduce1(Mat &image, int div = 64){
	int nl = image.rows;// number of lines
	int nc = image.cols*image.channels(); // total number of elements per line
	for (int j = 0; j < nl; j++){
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++){
			// process each pixel ---------------------
			// we could have equivalently used pointer arithmetic to
			//	move from column to column.So we could have written
			*data++ = *data / div*div + div / 2;

			// end of pixel processing ----------------
		}
	}
}
// using .ptr and * ++ and modulo
void colorReduce2(cv::Mat &image, int div = 64) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line

	for (int j = 0; j<nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++) {

			// process each pixel ---------------------
			//The reduced color could have also been computed using the modulo operator which brings us
			//	to the nearest multiple of div(the 1D reduction factor
			//But this computation is a bit slower because it requires reading each pixel value twice.

			int v = *data;
			*data++ = v - v%div + div / 2;

			// end of pixel processing ----------------

		} // end of line                   
	}
}
// using .ptr and * ++ and bitwise
void colorReduce3(cv::Mat &image, int div = 64) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// mask used to round the pixel value
	/*
		Another option would be to use bitwise operators. 
		Indeed, if we restrict the reduction factor to a power of 2, that is, div=pow(2,n), 
		then masking the first n bits of the pixel value would give us the nearest lower multiple of div. 
		This mask would be computed by a simple bit shift:
	*/
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	for (int j = 0; j<nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++) {

			// process each pixel ---------------------
			//The color reduction would be given by:
			*data++ = *data&mask + div / 2;
			/*
				In general, bitwise operations lead to very efficient code, 
				so they could constitute a powerful alternative when efficiency is a requirement.
			*/
			// end of pixel processing ----------------

		} // end of line                   
	}
}

void colorReduce8(Mat &image, int div = 64){
	//get iterators
	/*
		since image iterators are used to access the
		image elements, the return type must be known at compile time.
		The iterator is then declared as follows:
	*/
	//obtain iterator at initial position
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();

	//obtain end position
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	for (; it != itend; ++it){
		//process each pixel
		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;


	}

}
int _tmain(int argc, _TCHAR* argv[])
{
	Mat image1;
	image1 = imread("D:\\yuki-kimoto.jpg");
	colorReduce8(image1);
	namedWindow("Image");
	imshow("Image", image1);
	waitKey();
	return 0;
}

