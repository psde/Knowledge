#include <core/Producer.h>
#include <core/Consumer.h>
#include <core/DequePool.h>
#include <core/ConsumerProducer.h>

#include <opencv2/opencv.hpp>

#include <QObject>

class ImageConsumer : public QObject, public Consumer<cv::Mat>
{
	Q_OBJECT

signals:
	void imageChanged(cv::Mat image);

public:
	ImageConsumer(std::shared_ptr<Producer<cv::Mat> > producer)
		: Consumer<cv::Mat>(producer)
		, QObject()
	{
	}

	void consume(std::unique_ptr<cv::Mat> data)
	{
		cv::Mat frame = data->clone();
		recycleData(std::move(data));
		emit imageChanged(frame);
	}
};