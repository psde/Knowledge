#pragma once

// Qt
#include <QMainWindow>
#include <QtGui>
#include <qdebug.h>

// OpenCV
#include <opencv2/opencv.hpp>

// UI
#include "ui_MainWindow.h"

#include "ImageConsumer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui_MainWindow ui;
	ImageConsumer *_consumer;

private slots:
    void buttonClicked();
	void changeImage(cv::Mat image);

public:
	MainWindow(ImageConsumer* consumer);
    ~MainWindow();
};
