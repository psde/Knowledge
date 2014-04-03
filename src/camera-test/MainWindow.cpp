#include "MainWindow.h"

// Needs 32bit aligned image data!
QImage Mat2QImage(cv::Mat image)
{
	size_t width = image.size[1];
	size_t height = image.size[0];
	if (image.depth() == CV_8U && image.channels() == 3 && width % 4 == 0) {
		QImage qimg(image.data, width, height, QImage::Format_RGB888);
		return qimg.rgbSwapped();
	}
	else {
		qWarning() << "Image cannot be converted -- Depth: " << image.depth() << " channels: " << image.channels();
		return QImage();
	}
}

MainWindow::MainWindow(ImageConsumer *consumer)
: QMainWindow(0)
, _consumer(consumer)
{
	ui.setupUi(this);

	qRegisterMetaType<cv::Mat>("cv::Mat");

    // Connect slots
	connect(this->ui.dingeButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(_consumer, SIGNAL(imageChanged(cv::Mat)), this, SLOT(changeImage(cv::Mat)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonClicked()
{
    this->close();
}

void MainWindow::changeImage(cv::Mat image)
{
	this->ui.label->setPixmap(QPixmap::fromImage(Mat2QImage(image)));
}