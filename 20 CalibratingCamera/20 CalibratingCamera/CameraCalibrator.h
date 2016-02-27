#pragma once
#ifndef CAMERACALIBRATOR_H
#define CAMERACALIBRATOR_H

#include <vector>
#include <iostream>

#include "opencv2\core\core.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\calib3d\calib3d.hpp"
#include "opencv2\highgui\highgui.hpp"

using namespace std;
using namespace cv;
class CameraCalibrator
{
	//input points
	vector<vector<Point3f>> objectPoints;
	vector<vector<Point2f>> imagePoints;

	//output matrices
	Mat cameraMatrix;
	Mat distCoeffs;

	int flag;

	Mat map1, map2;
	bool mustInitUndistort;


public:
	CameraCalibrator() :flag(0), mustInitUndistort(true){
	};

	//open the chessboard images and extract corner points
	int addChessboardPoint(const vector<string>& filelist, Size & boardSize);
	// Add scene points and corresponding image points
	void addPoints(const vector<Point2f>& imageCorners, const vector<Point3f>& objectCorners);
	//calibrate the camera
	double Calibrate(Size &imageSize);
	//set the calibration flag
	void setCalibrationFlag(bool radial8CoefEnabled = false, bool tangentialParamEnabled = false);
	
	// Remove distortion in an image (after calibration)
	cv::Mat CameraCalibrator::remap(const cv::Mat &image);

	// Getters
	cv::Mat getCameraMatrix() { return cameraMatrix; }
	cv::Mat getDistCoeffs()   { return distCoeffs; }
};

#endif