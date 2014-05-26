#include <core/Producer.h>
#include <core/Consumer.h>
#include <core/DequePool.h>
#include <core/ConsumerProducer.h>

#include <opencv2/opencv.hpp>

#include "NamedWindow.h"

class CameraProducer : public Producer<cv::Mat>
{
private:
	cv::VideoCapture cap;

public:
	CameraProducer()
	: Producer<cv::Mat>(2)
	{
	}

	void onStart()
	{
		cap = cv::VideoCapture(0);

		if (!cap.isOpened())
		{
			std::cout << "Not initialized?" << std::endl;
			return;
		}
	}
	
	void onShutdown()
	{}

	std::unique_ptr<cv::Mat> produce(std::unique_ptr<cv::Mat> data)
	{
		cv::Mat* frame = data.release();
		cap >> *frame;
		NamedWindow::showNamedImage("CameraProducer", *frame);
		return std::unique_ptr<cv::Mat>(frame);
	}
};