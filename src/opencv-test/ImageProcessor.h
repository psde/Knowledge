#pragma once

#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

class ImageProcessor
{
  vector<int> compressionParameters;
  vector<vector<cv::Point>> recentContours;
  cv::Mat currentMaximaImage;
  cv::Mat recentMaximaImage;

public:
  ImageProcessor();
  bool calculateDifference(cv::Mat* image1, cv::Mat* image2, cv::Mat* result);
  bool calculateMoves(cv::Mat* image1, cv::Mat* image2, cv::Mat* result);
  void copyVectorOfVectorsIntoVector(vector<vector<cv::Point>>* vector1, vector<cv::Point2f>* vector2);
  void calcBinary(cv::Mat* image, cv::Mat* result);
  int displayMaxima(cv::Mat* image, cv::Mat* binaryImage);
  bool getGreyImage(cv::Mat* image);
  int getActivity(cv::Mat* image);
  bool storeImage(cv::Mat* image, string path);
  cv::Mat getRecentMaximaImage();
};