#include <stdio.h>
#include <opencv2/opencv.hpp>

int main( int argc, char** argv )
{
	cv::namedWindow("Named Window", CV_WINDOW_AUTOSIZE);
	cv::waitKey(0);
	return 0;
}