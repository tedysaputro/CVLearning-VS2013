// Creating and Print Matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "opencv2\core\core.hpp"
//Function declaration
void printMat1D(cv::Mat _m);

int _tmain(int argc, _TCHAR* argv[])
{
	//Create Matrices of different types and print them
	cv::Mat m1(4, 5, CV_8UC1, cv::Scalar(23));
	printMat1D(m1);

	cv::Mat m2(3, 2, CV_8SC1, cv::Scalar(-27));
	printMat1D(m2);

	cv::Mat m3(5, 3, CV_16UC1, cv::Scalar(1939));
	printMat1D(m3);

	cv::Mat m4(2, 4, CV_16SC1, cv::Scalar(-1961));
	printMat1D(m4);

	cv::Mat m5(5, 3, CV_32SC1, cv::Scalar(23985));
	printMat1D(m5);

	cv::Mat m6(2, 4, CV_32FC1, cv::Scalar(2011.02));
	printMat1D(m6);

	cv::Mat m7(2, 4, CV_64FC1, cv::Scalar(242012.36));
	printMat1D(m7);

	std::getchar();
	return 0;
}

void printMat1D(cv::Mat _m){
	int type = _m.type();

	switch (type){

		//unsigned 8-bits int
		case CV_8U:
			printf("\n --> Matrix type is CV_8U \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf("%d ", _m.at<uchar>(i, j));
				}
				printf("\n");
			}
			break;
	
		//Signed 8-bits int
		case CV_8S:
			printf("\n --> Matrix type is CV_8S \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf("%d", _m.at<schar>(i, j));
				}printf("\n");
			}
			break;
		//Unsigned 16 bits int
		case CV_16U:
			printf("\n --> Matrix type is CV_16U \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf(" %d ", _m.at<ushort>(i, j));
				}
				printf("\n");
			}
			break;

		//Signed 16-bits int
		case CV_16S:
			printf("\n --> Matrix type is CV_16S \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf(" %d ", _m.at<short>(i, j));
				}
				printf("\n");
			}
			break;

		//Signed 32-bits int
		case CV_32S:
			printf("\n --> Matrix type is CV_32S \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf(" %d ", _m.at<int>(i, j));
				}
				printf("\n");
			}
			break;

		//32 bits float
		case CV_32F:
			printf("\n --> Matrix type is CV_32F \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf(" %.3f ", _m.at<float>(i, j));
				}
				printf("\n");
			}
			break;

		//64 bit double
		case CV_64F:
			printf("\n --> Matrix type is CV_64F \n");
			for (size_t i = 0; i < _m.rows; i++){
				for (size_t j = 0; j < _m.cols; j++){
					printf(" %.3f ", _m.at<double>(i, j));
				}
				printf("\n");
			}
			break;
	}
}

