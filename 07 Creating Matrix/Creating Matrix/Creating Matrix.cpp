// Creating Matrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "opencv2\core\core.hpp"


int _tmain(int argc, _TCHAR* argv[])
{


	//Create a matrix (rows, cols, type, initial value)
	//We also initialize all the matrix elements to the value of 23 by using the last argument in the constructor.
	//Create a 2D-matrix of type 8UC1 (8-bit unsigned int)
	cv::Mat m(4, 5, CV_8UC1, cv::Scalar(23));

	//Print it 
	// First, we get the rows and columns values of our matrix by calling
	int rows = m.rows;
	int cols = m.cols;

	//Now we iterate over each row and each column with two for loops. 
	//Note that to access the elements we use the operator at with the type uchar since we are using a 8UC1 matrix
	printf("Matrix m: \n");
	printf(" Matrix m: \n");
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			// Observe the type used in the template
			printf(" %d  ", m.at<uchar>(i, j));
		}
		printf("\n");
	}
	std::getchar();
	return 0;
}

