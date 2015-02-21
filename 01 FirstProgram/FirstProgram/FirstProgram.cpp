// FirstProgram.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\highgui\highgui.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
		loads the image.* The function cvLoadImage() is a high-level routine that determines 
		the file format to be loaded based on the file name; it also automatically allocates
		the memory needed for the image data structure. 
		
		Note that cvLoadImage() can read a wide variety of image formats, 
		including BMP, DIB, JPEG, JPE, PNG, PBM, PGM, PPM, SR, RAS, and TIFF. 
		
		A pointer to an allocated image data structure is then returned. 
		This structure, called IplImage, is the OpenCV construct with which you will deal the most. 
		
		OpenCV uses this structure to handle all kinds of images: single-channel, multichannel, integer-valued, floating-point-valued, et cetera. 
		We use the pointer thatcvLoadImage() returns to manipulate the image and the image data.
	*/
	IplImage* img = cvLoadImage("D:\\yuki-kimoto-012.jpg");

	/*
		cvNamedWindow(), opens a window on the screen that can contain and display an image. 
		This function, provided by the HighGUI library, also assigns a name to the window (in this case, "Example1"). 
		
		Future HighGUI calls that interact with this window will refer to it by this name.
		
		The second argument to cvNamedWindow() defines window properties. It may be set either
		to 0 (the default value) or to CV_WINDOW_AUTOSIZE. In the former case, the size of the
		window will be the same regardless of the image size, and the image will be scaled to
		fit within the window. In the latter case, the window will expand or contract automatically
		when an image is loaded so as to accommodate the image’s true size.
	*/
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);

	/*
		Whenever we have an image in the form of an IplImage* pointer, we can display it in an
		existing window with cvShowImage(). The cvShowImage() function requires that a named
		window already exist (created by cvNamedWindow()). On the call to cvShowImage(), 
		the window will be redrawn with the appropriate image in it, and the window will resize
		itself as appropriate if it was created using the CV_WINDOW_AUTOSIZE flag
	*/
	cvShowImage("Example1", img);
	/*
		The cvWaitKey() function asks the program to stop and wait for a keystroke. If a positive
		argument is given, the program will wait for that number of milliseconds and then continue
		even if nothing is pressed. If the argument is set to 0 or to a negative number, the
		program will wait indefinitely for a keypress.
	*/
	cvWaitKey(0);
	/*
		Once we are through with an image, we can free the allocated memory. OpenCV expects
		a pointer to the IplImage* pointer for this operation. Aft er the call is completed,
		the pointer img will be set to NULL.

		Finally, we can destroy the window itself. The function cvDestroyWindow() will close the
		window and de-allocate any associated memory usage (including the window’s internal
		image buffer, which is holding a copy of the pixel information from *img). 
		
		For a simple program, you don’t really have to call cvDestroyWindow() or cvReleaseImage() because all
		the resources and windows of the application are closed automatically by the operating
		system upon exit, but it’s a good habit anyway
	*/
	cvReleaseImage(&img);
	cvDestroyWindow("Example1");
	return 0;
}

