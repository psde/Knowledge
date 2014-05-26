#pragma once

#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

class ImageProcessor
{
  vector<int> compressionParameters;

public:
  ImageProcessor();
  bool calculateDifference(cv::Mat* image1, cv::Mat* image2, cv::Mat* result);
  int displayMaxima(cv::Mat* image);
  bool getGreyImage(cv::Mat* image);
  int getActivity(cv::Mat* image);
  bool storeImage(cv::Mat* image, string path);
};