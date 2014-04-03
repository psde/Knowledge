#include <core/Producer.h>
#include <core/Consumer.h>
#include <core/DequePool.h>
#include <core/ConsumerProducer.h>

#include <opencv2/opencv.hpp>

class ImageConsumerProducer : public ConsumerProducer<cv::Mat, cv::Mat>
{
public:
	ImageConsumerProducer(std::shared_ptr<Producer<cv::Mat>> producer, size_t maxQueueSize)
	: ConsumerProducer(producer, maxQueueSize)
	{
	}

	void onStart()
	{
		cv::namedWindow("ImageConsumerProducer", 1);
	}

	std::unique_ptr<cv::Mat> process(std::unique_ptr<cv::Mat> inData, std::unique_ptr<cv::Mat> outData)
	{
		cv::Mat* frame = new cv::Mat(inData->size(), inData->type());
		inData->copyTo(*frame);
		recycleData(std::move(inData));

		cv::imshow("ImageConsumerProducer", *frame);
		cvWaitKey(1);

		return std::unique_ptr<cv::Mat>(frame);
	}
};
