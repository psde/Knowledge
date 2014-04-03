#include <QApplication>

#include "CameraProducer.h"
#include "ImageConsumerProducer.h"

#include "MainWindow.h"

int main(int argc, char **argv)
{
	std::shared_ptr<CameraProducer> camProducer(new CameraProducer());
	std::shared_ptr<ImageConsumerProducer> imageConsumerProducer(new ImageConsumerProducer(camProducer, 2));
	std::shared_ptr<ImageConsumer> imageConsumer(new ImageConsumer(imageConsumerProducer));

	std::thread t0(&CameraProducer::start, camProducer);
	std::thread t1(&ImageConsumerProducer::start, imageConsumerProducer);
	std::thread t2(&ImageConsumer::start, imageConsumer);

	QApplication app(argc, argv);

	MainWindow mainWindow(imageConsumer.get());
	mainWindow.show();

	app.exec();

	imageConsumerProducer->shutdown();
	camProducer->shutdown();
	imageConsumer->shutdown();

	t0.join();
	t1.join();
	t2.join();

	return 0;
}
