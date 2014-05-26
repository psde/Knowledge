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

class Graph {
public:
    Graph(int minValue, 
            int maxValue, 
            uint width, 
            uint height,
            uint numberOfValues,
            std::string imageName);
    
    void display();
    void updateValues(uint* values, uint numberOfValues);
    void updateValue(uint value);
    void setValueRange(uint minValue, uint maxValue);
    virtual ~Graph();
private:
    std::string imageName;
    std::list<uint> values;

    cv::Mat* image;
    uint numberOfValues;
    uint minValue;
    uint maxValue;
    
    uint width;
    uint heigth;
    
};

#endif	/* GRAPH_H */

