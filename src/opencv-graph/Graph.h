/* 
 * File:   Graph.h
 * Author: christian
 *
 * Created on 26. Mai 2014, 17:12
 */

#ifndef GRAPH_H
#define	GRAPH_H
#include <string>
#include <list>
#include <opencv2/opencv.hpp>
#include <mutex>

class Graph {
public:
    Graph(int minValue, 
            int maxValue, 
            unsigned int width, 
            unsigned int height,
            unsigned int numberOfValues,
            std::string imageName);
    std::mutex myMutex;
    void display();
    void updateValues(unsigned int* values, unsigned int numberOfValues);
    void updateValue(unsigned int value);
    void setValueRange(unsigned int minValue, unsigned int maxValue);
    virtual ~Graph();
private:
    std::string imageName;
    std::list<unsigned int> values;
    void updateValuePr(unsigned int value);
    
    cv::Mat* image;
    unsigned int numberOfValues;
    unsigned int minValue;
    unsigned int maxValue;
    
    unsigned int width;
    unsigned int heigth;
    
};

#endif	/* GRAPH_H */

