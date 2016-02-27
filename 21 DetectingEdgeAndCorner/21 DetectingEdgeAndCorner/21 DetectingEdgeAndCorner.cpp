// 21 DetectingEdgeAndCorner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "morphofeatures.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("building.jpg");
	if (!image.data)
		return 0;

	namedWindow("Image");
	imshow("Image", image);

	//create the morphological features
	MorphoFeatures morpho;
	morpho.setThreshold(40);

	//get the edges
	Mat edges;
	edges = morpho.getEdges(image);

	//display the edges image
	namedWindow("Edge Image");
	imshow("Edge Image", edges);

	//get the corners
	morpho.setThreshold(-1);
	Mat corners;
	corners = morpho.getCorners(image);
	morphologyEx(corners, corners, MORPH_TOPHAT, Mat());
	threshold(corners, corners, 40, 255, THRESH_BINARY_INV);
	
	// Display the corner image

	namedWindow("Corner Image");
	imshow("Corner Image", corners);

	// Display the corner on the image
	morpho.drawOnImage(corners, image);
	namedWindow("corners on image");
	imshow("corners on image", image);
	
	waitKey();

	return 0;
}

