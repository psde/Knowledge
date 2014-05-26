#pragma once

// Qt
#include <QMainWindow>
#include <QtGui>
#include <qdebug.h>

// Std
#include <memory>

// OpenCV
#include <opencv2/opencv.hpp>

#include "QtHelper.h"

class NamedWindow : public QObject
{
	Q_OBJECT
private:
	QHash<QString, QLabel*> _labels;

private slots :
	void showOrCreateLabelImage(QString window, cv::Mat image)
	{
		QLabel *label = _labels[window];
		if (label == nullptr)
		{
			label = new QLabel(window);
			label->setWindowTitle(window);
		}
		label->setPixmap(QPixmap::fromImage(Mat2QImage(image)));
		label->show();
		_labels[window] = label;
	}

signals:
	void showImage(QString window, cv::Mat image);

public:
	NamedWindow(QObject *parent = 0)
	: QObject(parent)
	{
		connect(this, SIGNAL(showImage(QString, cv::Mat)), this, SLOT(showOrCreateLabelImage(QString, cv::Mat)));
	}

	void emitShowImage(QString window, cv::Mat image)
	{
		emit showImage(window, image);
	}

	static std::shared_ptr<NamedWindow>* instance()
	{
		static std::shared_ptr<NamedWindow> instance;
		return &instance;
	}

	static void showNamedImage(QString window, cv::Mat image)
	{
		std::shared_ptr<NamedWindow> instance = *NamedWindow::instance();
		if (instance == nullptr)
			return;
		instance->emitShowImage(window, image);
	}
};
