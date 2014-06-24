#pragma once

#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

class ImageProcessor
{
  vector<int> compressionParameters;
  vector<vector<cv::Point>> recentContours;

public:
  ImageProcessor();
  /*
  Calculates a difference image from image1 and image2 which is stored in result.
  */
  bool calculateDifference(cv::Mat* image1, cv::Mat* image2, cv::Mat* result);

  /*
  Calculates moves from image1 and image2 with optical flow. The optical flow is inserted into result (as red lines).
  */
  bool calculateMoves(cv::Mat* image1, cv::Mat* image2, cv::Mat* result);
  
private:
  void copyVectorOfVectorsIntoVector(vector<vector<cv::Point>>* vector1, vector<cv::Point2f>* vector2);
public:
  /*
  Calculates a binary image from image with a fixed threshold. The binary image is stored in result.
  */
  void calculateBinary(cv::Mat* image, cv::Mat* result);

  /*
  Highlights areas from image with high activity.
  */
  int displayMaxima(cv::Mat* image, cv::Mat* binaryImage);

  /*
  Converts an image into a grey image.
  */
  bool getGreyImage(cv::Mat* image);

  /*
  Calculates an activity value from image to be shown in a graph.
  */
  int getActivity(cv::Mat* image);

  /*
  Stores image at the given path.
  */
  bool storeImage(cv::Mat* image, string path);
};