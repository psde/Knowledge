#include "ImageProcessor.h"

ImageProcessor::ImageProcessor()
{
  compressionParameters.push_back(CV_IMWRITE_PNG_COMPRESSION);
  compressionParameters.push_back(0);

}

bool ImageProcessor::calculateDifference(cv::Mat* image1, cv::Mat* image2, cv::Mat* result)
{
  if (image1->empty() || image2->empty())
  {
    return false;
  }

  if (!((image1->size == image2->size) && (image2->size == result->size) && (image1->channels() == image2->channels()) && (image2->channels() == result->channels()))) // TODO depth???
  {
    return false;
  }

  int counter = 0;
  uchar* source1 = image1->ptr();
  uchar* source2 = image2->ptr();
  uchar* destination = result->ptr();
  int limit = image1->rows * image1->cols * image1->channels();
  while (counter < limit)
  {
    *destination = (*source1 - *source2 + (int)sizeof(uchar)) / 2;
    source1++;
    source2++;
    destination++;
    counter++;
  }

  return true;
}

int ImageProcessor::displayMaxima(cv::Mat* image)
{
  cv::Mat binaryImage;
  binaryImage.reshape(1);
  if (image != NULL)
  {
    cv::threshold(*image, binaryImage, UCHAR_MAX - 1, UCHAR_MAX, CV_THRESH_BINARY);
    vector<vector<cv::Point>> contours;
    cv::findContours(binaryImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    cv::drawContours(*image, contours, -1, cv::Scalar(UCHAR_MAX, 0, 0));
    return (int)(contours.size());
  }
  return -1;
}

bool ImageProcessor::getGreyImage(cv::Mat* image)
{
  if (image != NULL)
  {
    cv::cvtColor(*image, *image, CV_RGB2GRAY);
    return true;
  }
  return false;
}

int ImageProcessor::getActivity(cv::Mat* image)
{
  if (image->channels() == 1)
  {
    cv::Scalar meanValue;
    meanValue = cv::mean(*image);
    return meanValue[0];
  }
  return -1;
}

bool ImageProcessor::storeImage(cv::Mat* image, string path)
{
  if (image != NULL)
  {
    return cv::imwrite(path, *image, compressionParameters);
  }
  return false;
}