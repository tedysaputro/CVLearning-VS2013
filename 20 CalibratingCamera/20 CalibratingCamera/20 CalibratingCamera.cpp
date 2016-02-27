// 20 CalibratingCamera.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\features2d\features2d.hpp>

#include "CameraCalibrator.h"

using namespace cv;
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	
	namedWindow("Image");
	Mat image;
	std::vector<std::string> filelist;

	// generate list of chessboard image filename
	for (int i = 1; i <= 20; i++) {

		std::stringstream str;
		str << "chessboards/chessboard" << std::setw(2) << std::setfill('0') << i << ".jpg";
		std::cout << str.str() << std::endl;

		filelist.push_back(str.str());
		image = cv::imread(str.str(), 0);
		cv::imshow("Image", image);

		cv::waitKey(100);
	}

	CameraCalibrator cameraCalibrator;
	Size boardSize(6, 4);
	cameraCalibrator.addChessboardPoint(
		filelist,		//filenames of chessboard image
		boardSize);		//size of chessboard
	cameraCalibrator.calibrate(image.size());
	return 0;
}

