#pragma once

// Qt
#include <QMainWindow>
#include <QtGui>
#include <qdebug.h>

// OpenCV
#include <opencv2/opencv.hpp>

// Needs 32bit aligned image data!
static QImage Mat2QImage(cv::Mat image)
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
