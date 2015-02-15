// SecondProgram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\highgui\highgui.hpp"


int _tmain(int argc, _TCHAR* argv[])
{

	cvNamedWindow("Example 2", CV_WINDOW_AUTOSIZE);

	/*
	The function cvCreateFileCapture() takes as path of AVI file to be
	loaded and then returns a pointer to a CvCapture structure. 
	
	This structure contains all of the information about the AVI file being read, including state information. 
	
	When created in this way, the CvCapture structure is initialized to the beginning of the AVI.
	*/
	CvCapture* capture = cvCreateFileCapture("D:\\Personal\\03 BEY\\BEY TV\\Dioda\\dioda2.avi");
	IplImage* frame;
	while (1){
		/*
		Once inside of the while(1) loop, we begin reading from the AVI file. 
		
		cvQueryFrame() takes as its argument a pointer to a CvCapture structure. 
		It then grabs the next video frame into memory (memory that is actually part of the CvCapture structure). 
		A pointer is returned to that frame. 
		
		Unlike cvLoadImage, which actually allocates memory for the image, 
		cvQueryFrame uses memory already allocated in the CvCapture structure. Thus it
		will not be necessary (or wise) to call cvReleaseImage() for this “frame” pointer. Instead,
		the frame image memory will be freed when the CvCapture structure is released.
		*/
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage("Example2", frame);

		/*
		Once we have displayed the frame, we then wait for 33 ms.
		* If the user hits a key, then c will be set to the ASCII value of that key; if not, then it will be set to –1. 
		If the user hits the Esc key (ASCII 27), then we will exit the read loop. 
		Otherwise, 33 ms will pass and we will just execute the loop again.
		
		It is worth noting that, in this simple example, we are not explicitly controlling the speed of the video in any intelligent way. 
		We are relying solely on the timer in cvWaitKey() to pace the loading of frames. 
		
		In a more sophisticated application it would be wise to read the actual frame rate from the CvCapture structure (from the AVI) and
		behave accordingly!
				
		*/
		char c = cvWaitKey(33);
		if (c == 27) break;


	}

	/*
	When we have exited the read loop—because there was no more video data 
	or because the user hit the Esc key—we can free the memory associated with the CvCapture structure.
	This will also close any open file handles to the AVI file.
	*/
	cvReleaseCapture(&capture);
	cvDestroyWindow("Example2");




	return 0;
}

