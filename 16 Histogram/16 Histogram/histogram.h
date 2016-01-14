#if !defined HISTOGRAM
#define HISTOGRAM

#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
class histogram1D
{
private:
	int histSize[1];//number of bins
	float hranges[2];//min and max pixel value
	const float* ranges[1];
	int channels[1];
public:
	histogram1D();
	// Sets the channel on which histogram will be calculated.
	// By default it is channel 0.
	void setChannel(int c);
	// Gets the channel used.
	int getChannel();
	// Sets the range for the pixel values.
	// By default it is [0,255]
	void setRange(float minValue, float maxValue);
	// Gets the min pixel value.
	float getMinValue();
	// Gets the max pixel value.
	float getMaxValue();\
	// Sets the number of bins in histogram.
	// By default it is 256.
	void setNBins(int nbins);
	// Gets the number of bins in histogram.
	int getNBins();
	//Computes the 1D histogram
	MatND getHistogram(const Mat &image);
	// Computes the 1D histogram and returns an image of it.
	Mat getHistogramImage(const Mat &image);
	// Equalizes the source image.
	Mat equalize(const Mat &image);
	// Stretches the source image.
	Mat strecth(const Mat &image, int minValue);
	// Applies a lookup table transforming an input image into a 1-channel image
	Mat applyLookUp(const Mat& image, const MatND& lookup);


	
};

#endif