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

  if (!((image1->size == image2->size) && (image2->size == result->size) && (image1->channels() == image2->channels()) && (image2->channels() == result->channels()) && (image2->depth() == image1->depth())))
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
    *destination = abs(*source1 - *source2);
    source1++;
    source2++;
    destination++;
    counter++;
  }

  return true;
}

bool ImageProcessor::calculateMoves(cv::Mat* image1, cv::Mat* image2, cv::Mat* result)
{
  if (image1->empty() || image2->empty())
  {
    return false;
  }

  if (!((image1->size == image2->size) && (image2->size == result->size) && (image1->channels() == image2->channels()) && (image1->depth() == image2->depth())))
  {
    return false;
  }

  if (!(this->recentContours.empty()))
  {
    cv::vector<cv::Point2f> previousPoints;
    this->copyVectorOfVectorsIntoVector(&(this->recentContours), &previousPoints);
    cv::vector<cv::Point2f> nextPoints;
    cv::vector<unsigned char> status;
    cv::vector<float> errors;
    cv::calcOpticalFlowPyrLK(*image1, *image2, previousPoints, nextPoints, status, errors);
    vector<cv::Point2f, allocator<cv::Point2f>>::const_iterator previousPoint = previousPoints.begin();
    vector<cv::Point2f, allocator<cv::Point2f>>::const_iterator nextPoint = nextPoints.begin();
    while (previousPoint != previousPoints.end())
    {
      if (nextPoint == nextPoints.end())
      {
        return false;
      }

      cv::line(*result, cv::Point(previousPoint->x, previousPoint->y), cv::Point(nextPoint->x, nextPoint->y), cv::Scalar(0.0, 0.0, 255.0));
      previousPoint++;
      nextPoint++;

      return true;
    }
  }
  return false;
}

void ImageProcessor::copyVectorOfVectorsIntoVector(vector<vector<cv::Point>>* vector1, vector<cv::Point2f>* vector2)
{
  vector<vector<cv::Point>>::const_iterator vector1OfVectorsIterator = vector1->begin();
  while (vector1OfVectorsIterator != vector1->end())
  {
    vector<cv::Point>::const_iterator vector1Iterator = vector1OfVectorsIterator->begin();
    while (vector1Iterator != vector1OfVectorsIterator->end())
    {
      vector2->push_back(cv::Point2f((float)vector1Iterator->x, (float)vector1Iterator->y));
      vector1Iterator++;
    }
    vector1OfVectorsIterator++;
  }
}

void ImageProcessor::calculateBinary(cv::Mat* image, cv::Mat* result)
{
  cv::threshold(*image, *result, 25, UCHAR_MAX, CV_THRESH_BINARY);
}

int ImageProcessor::displayMaxima(cv::Mat* image, cv::Mat* binaryImage)
{
  if (image != NULL && binaryImage != NULL)
  {
    vector<vector<cv::Point>> contours;
    cv::findContours(*binaryImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    this->recentContours = contours;
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
    int counter = 0;
    uchar* source = image->ptr();
    uchar* end = source +  image->rows * image->cols * image->channels();
    while (source < end)
    {
      if (*source > 10)
      {
        counter++;
      }
      source++;
    }
    return counter;
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