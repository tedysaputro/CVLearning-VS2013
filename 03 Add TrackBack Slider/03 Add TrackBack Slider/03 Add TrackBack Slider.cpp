// 03 Add TrackBack Slider.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"

#include <stdio.h>

using namespace std;
/*
	define a global variable for the slider position. The callback will need access to
	the capture object, so we promote that to a global variable. 
	
	Because we are nice people and like our code to be readable and easy to understand, 
	we adopt the convention of adding a leading g_ to any global variable.
*/
int        g_slider_position = 0;
CvCapture* g_capture = NULL;

/*
	Now we define a callback routine to be used when the user pokes the slider. Th is routine
	will be passed to a 32-bit integer, which will be the slider position

	The call to cvSetCaptureProperty() is one we will see often in the future, along with its
	counterpart cvGetCaptureProperty(). These routines allow us to configure (or query in
	the latter case) various properties of the CvCapture object. 
	
	In this case we pass the argument CV_CAP_PROP_POS_FRAMES, which indicates that we would like to set the read position
	in units of frames. 
	(We can use AVI_RATIO instead of FRAMES if we want to set the position as a fraction of the overall video length). 
	
	Finally, we pass in the new value of the position.
	
	Because HighGUI is highly civilized, it will automatically handle such issues as
	the possibility that the frame we have requested is not a key-frame; it will start at the
	previous key-frame and fast forward up to the requested frame without us having to
	fuss with such details.
*/
void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(
		g_capture,
		CV_CAP_PROP_POS_FRAMES,
		pos
		);
}

//Hack because sometimes the number of frames in a video is not accessible. 
//Probably delete this on Widows
int getAVIFrames(char * fname) {
	char tempSize[4];
	// Trying to open the video file
	ifstream  videoFile(fname, ios::in | ios::binary);
	// Checking the availablity of the file
	if (!videoFile) {
		cout << "Couldn’t open the input file " << fname << endl;
		exit(1);
	}
	// get the number of frames
	videoFile.seekg(0x30, ios::beg);
	videoFile.read(tempSize, 4);
	int frames = (unsigned char)tempSize[0] + 0x100 * (unsigned char)tempSize[1] + 0x10000 * (unsigned char)tempSize[2] + 0x1000000 * (unsigned char)tempSize[3];
	videoFile.close();
	return frames;
}


int main(int argc, char** argv) {
	cvNamedWindow("Example2_3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture("D:\\Personal\\03 BEY\\BEY TV\\Dioda\\dioda2.avi");
	IplImage *foo = cvQueryFrame(g_capture);

	/*
		As promised, we use cvGetCaptureProperty() when we want to query some data from the
		CvCapture structure. In this case, we want to find out how many frames are in the video
		so that we can calibrate the slider (in the next step).

	
	*/
	int frames = (int)cvGetCaptureProperty(
		g_capture,
		CV_CAP_PROP_FRAME_COUNT
		);

	int tmpw = (int)cvGetCaptureProperty(
		g_capture,
		CV_CAP_PROP_FRAME_WIDTH
		);

	int tmph = (int)cvGetCaptureProperty(
		g_capture,
		CV_CAP_PROP_FRAME_HEIGHT
		);

	printf("opencv frames %d w %d h %d\n", frames, tmpw, tmph);

	frames = getAVIFrames("D:\\Personal\\03 BEY\\BEY TV\\Dioda\\dioda2.avi"); //This is a hack because on linux, getting number of frames often doesn't work

	printf("hacked frames %d w %d h %d\n", frames, tmpw, tmph);
	/*
		The function cvCreateTrackbar() allows us to give the trackbar a label* (in this case Position) 
		and to specify a window to put the trackbar in. 
		
		We then provide a variable that will be bound to the trackbar, the maximum
		value of the trackbar, and a callback (or NULL if we don’t want one) for when the
		slider is moved. Observe that we do not create the trackbar if cvGetCaptureProperty()
		returned a zero frame count. 
		
		This is because sometimes, depending on how the video was encoded, the total number of frames will not be available. 
		In this case we will just play the movie without providing a trackbar.
	*/
	cvCreateTrackbar(
		"Position",
		"Example2_3",
		&g_slider_position,
		frames,
		onTrackbarSlide
		);


	IplImage* frame;
	frames = 0;
	while (1) {
		frame = cvQueryFrame(g_capture);
		if (!frame) break;
		//      int frames = cvGetCaptureProperty( g_capture, CV_CAP_PROP_POS_FRAMES);//This should work, sometimes it does not on linux
		frames++; //My cheat
		printf("\nFrame number=%d\n", frames);
		cvSetTrackbarPos("Position", "Example2_3", frames);
		cvShowImage("Example2_3", frame);
		char c = (char)cvWaitKey(10);
		if (c == 27) break;
	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("Example2_3");
	return(0);
}
