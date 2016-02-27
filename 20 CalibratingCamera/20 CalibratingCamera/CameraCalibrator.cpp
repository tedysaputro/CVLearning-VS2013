#include "stdafx.h"
#include "CameraCalibrator.h"






int CameraCalibrator::addChessboardPoint(const vector<string>& filelist, 
									Size &boardSize){
	//the points of the chessboard
	vector<Point2f> imageCorners;
	vector<Point3f> objectCorners;

	//3d Scene Points
	//Initialize the chessboard corners
	//in the chessboard reference frame
	//the corners are at 3D location (X, Y, Z)=(i,j,0)
	for (int i = 0; i < boardSize.height; i++){
		for (int j = 0; j < boardSize.width; j++){
			objectCorners.push_back(Point3f(i, j, 0.0f));
		}
	}


	//2D image points
	Mat image;
	int successes=0;
	//for al viewpoints

	for (int i = 0; i < filelist.size(); i++){
		//open the image
		image = imread(filelist[i], 0);
		//get the chessboard corners
		bool found = findChessboardCorners(image, boardSize, imageCorners);

		//get the subpixel accuracy on the corners
		cornerSubPix(image, imageCorners, Size(5, 5), Size(-1, -1),
			TermCriteria(cv::TermCriteria::MAX_ITER +
			cv::TermCriteria::EPS,
			30,		// max number of iterations 
			0.1));     // min accuracy

		//if we have a good board, add it to our data
		if (imageCorners.size() == boardSize.area()){
			addPoints(imageCorners, objectCorners);
			successes++;

		}
		//draw the corners
		drawChessboardCorners(image, boardSize, imageCorners, found);
		imshow("Corners on chessboard", image);
		waitKey(100);

	}
	return successes;

}

//add scene points and corrsponding image points
void CameraCalibrator::addPoints(const vector<Point2f>& imageCorners, const vector<cv::Point3f>& objectCorners){
	//2D image points from one view
	imagePoints.push_back(imageCorners);
	//corresponding 3D scene points
	objectPoints.push_back(objectCorners);

}

//calibrate the camera
//return the re-projection error
double CameraCalibrator::Calibrate(Size &imageSize){
	//undistorted must be reinitialized
	mustInitUndistort = true;
	//output rotations and translations
	vector<Mat> rvecs, tvecs;

	return
		calibrateCamera(objectPoints,
						imagePoints,
						imageSize,
						cameraMatrix,
						distCoeffs,
						rvecs, tvecs,
						flag);

	 
}

//remove distortion in an image (after calibration)
Mat CameraCalibrator::remap(const Mat &image){
	Mat undistorted;
	if (mustInitUndistort){//called once per calibration
		initUndistortRectifyMap(cameraMatrix,
			distCoeffs,
			Mat(),
			Mat(),
			Size(640, 480),
			CV_32FC1,
			map1, map2);
		mustInitUndistort = false;
		
	}
	cv::remap(image, undistorted, map1, map2, INTER_LINEAR);

	return undistorted;
}

// Set the calibration options
// 8radialCoeffEnabled should be true if 8 radial coefficients are required (5 is default)
// tangentialParamEnabled should be true if tangeantial distortion is present
void CameraCalibrator::setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled){
	//set the flag used in cv::calibrateCamera();
	flag = 0;
	if (!tangentialParamEnabled)
		flag += CV_CALIB_ZERO_TANGENT_DIST;
	if (radial8CoeffEnabled)
		flag += CV_CALIB_RATIONAL_MODEL;
}