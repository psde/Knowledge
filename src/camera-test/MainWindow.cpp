#include "QtHelper.h"
#include "NamedWindow.h"
#include "MainWindow.h"

MainWindow::MainWindow(ImageConsumer *consumer)
: QMainWindow(0)
, _consumer(consumer)
{
	ui.setupUi(this);
	
    // Connect slots
	connect(this->ui.dingeButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(_consumer, SIGNAL(imageChanged(cv::Mat)), this, SLOT(changeImage(cv::Mat)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonClicked()
{
    NamedWindow::instance()->reset();
    QCoreApplication::exit();
    this->close();
}

void MainWindow::changeImage(cv::Mat image)
{
	this->ui.label->setPixmap(QPixmap::fromImage(Mat2QImage(image)));
}