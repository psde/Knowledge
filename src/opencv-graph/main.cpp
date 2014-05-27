#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "Graph.h"

int main( int argc, char** argv )
{
	(void) argc;
	(void) argv;
	// minValue, maxValue, width, height, numberOfValues, imageName
	Graph graph(0, 100, 500, 500, 1000, "imageName");
	graph.display();
	for(unsigned int i = 0; i < 10000; i ++){
		graph.updateValue(i%100);
		graph.display();
		cv::waitKey(50);
	}
	cv::waitKey();
	return 0;
}