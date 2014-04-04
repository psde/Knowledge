#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(int /*argc*/, char** /*argv*/)
{       
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Not initialized?" << std::endl;
        return -1;
    }

	cv::namedWindow("Camera", CV_WINDOW_AUTOSIZE);

    while(true)
    {
        cv::Mat frame;
        cap >> frame;
        cv::imshow("Camera", frame);

        int key = cv::waitKey(1);   
        if(key > 0)
            break;
    }
	return 0;
}