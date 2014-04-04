#include <core/Producer.h>
#include <core/Consumer.h>
#include <core/DequePool.h>
#include <core/ConsumerProducer.h>

#include <opencv2/opencv.hpp>

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
		//cv::namedWindow("CameraProducer", 1);
		cap = cv::VideoCapture(0);

		if (!cap.isOpened())
		{
			std::cout << "Not initialized?" << std::endl;
			return;
		}
	}

	std::unique_ptr<cv::Mat> produce(std::unique_ptr<cv::Mat> data)
	{
		cv::Mat* frame = data.release();
		//cap.retrieve(*frame);
		cap >> *frame;
		//cv::imshow("CameraProducer", *frame);
		//cvWaitKey(1);
		return std::unique_ptr<cv::Mat>(frame);
	}
};