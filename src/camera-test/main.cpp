#include <QApplication>

#include "CameraProducer.h"
#include "ImageProcessor.h"

#include "MainWindow.h"
#include "NamedWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	// Non-Qt types must be registred to be able to be used in the Qt connection system
	qRegisterMetaType<cv::Mat>("cv::Mat");

	// Reset the NamedWindow workaround thingy
	NamedWindow::instance()->reset(new NamedWindow(&app));

	// Create and start all producer/consumer/...
	std::shared_ptr<CameraProducer> camProducer(new CameraProducer());
	std::shared_ptr<ImageProcessor> imageProcessor(new ImageProcessor(camProducer, 2));
	std::shared_ptr<ImageConsumer> imageConsumer(new ImageConsumer(imageProcessor));

	std::thread t0(&CameraProducer::start, camProducer);
	std::thread t1(&ImageProcessor::start, imageProcessor);
	std::thread t2(&ImageConsumer::start, imageConsumer);
	
	// Create main window and start application
	MainWindow mainWindow(imageConsumer.get());
	mainWindow.show();

	app.exec();

	// Shutdown
	imageProcessor->shutdown();
	camProducer->shutdown();
	imageConsumer->shutdown();

	t0.join();
	t1.join();
	t2.join();

	return 0;
}
