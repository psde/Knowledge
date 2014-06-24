#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <string>
#include "ImageProcessor.h"
#include "../opencv-graph/Graph.h"

using namespace std;

int main(int /*argc*/, char** /*argv*/)
{       
    cv::VideoCapture videoCapture(0);
    ImageProcessor imageProcessor = ImageProcessor();
    Graph* graph = new Graph(0, 50, 500, 300, 500, "Graph");

    if (!videoCapture.isOpened())
    {
        std::cout << "Not initialised?" << std::endl;
        return -1;
    }

	cv::namedWindow("Camera", CV_WINDOW_AUTOSIZE);
  cv::Mat* frame;
  frame = new cv::Mat();
  videoCapture >> *frame;
  videoCapture >> *frame;
  videoCapture >> *frame;
  videoCapture >> *frame;
  videoCapture >> *frame;
  videoCapture >> *frame;
  videoCapture >> *frame;
  cv::Mat* frame2;
  frame2 = new cv::Mat();
  cv::Mat* difference;
  difference = new cv::Mat();
  cv::Mat* binary;
  binary = new cv::Mat();
  int counter = 1;
  string path;
  string path1 = "..\\..\\..\\src\\opencv-test\\Images\\";
  char* path2 = new char[7];
  string path3 = "_Image.png";

  bool stop = false;
  while(!stop)
    {
    videoCapture >> *frame2;
    cv::imshow("Camera", *frame2);
        difference->create(frame->rows, frame->cols, frame->type());
        if (imageProcessor.calculateDifference(frame, frame2, difference))
        {
          if (imageProcessor.getGreyImage(difference))
          {
            cv::medianBlur(*difference, *difference, 5);
            cv::imshow("Difference", *difference);
            imageProcessor.calcBinary(difference, binary);
            cv::imshow("Binary", *binary);
            if (imageProcessor.displayMaxima(difference, binary) > -1)
            {
              int activity = imageProcessor.getActivity(difference);
              cout << activity << endl;
              if (activity >= 0)
              {
                graph->updateValue(activity);
                graph->display();
              }
              cv::imshow("Maxima", *difference);

              if (imageProcessor.calculateMoves(&(imageProcessor.getRecentMaximaImage()), difference, frame2))
              {
                cv::imshow("Optical Flow", *frame2);
              }
            }
          }
        }
        
        sprintf(path2, "%06d", counter++);
        path = path1 + path2 + path3;
        //imageProcessor.storeImage(frame, path);
        cv::Mat* copy = frame;
        frame = frame2;
        frame2 = copy;
        int key = cv::waitKey(1);   
        if (key > 0)
        {
          stop = true;
        }
    }
	return 0;
}