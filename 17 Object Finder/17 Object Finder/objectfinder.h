#if !defined OFINDER
#define OFINDER

#include <opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
class ObjectFinder
{
private:
	float hranges[2];
	const float* ranges[3];
	int channels[3];

	float threshold;
	MatND histogram;
	SparseMat shistogram;
	bool isSparse;
public:
	ObjectFinder();
	void setThreshold(float t);
	// Gets the threshold
	float getThreshold();
	// Sets the reference histogram
	void setHistogram(const MatND& h);
	// Sets the reference histogram
	void setHistogram(const SparseMat& h);
	//finds the pixels belonging to the histogram
	Mat find(const Mat& image);
	Mat find(const Mat& image, float minValue, float maxValue, int *channels, int dim);
};

#endif