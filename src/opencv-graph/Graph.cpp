/* 
 * File:   Graph.cpp
 * Author: christian
 * 
 * Created on 26. Mai 2014, 17:12
 */

#include "Graph.h"
#include "opencv2/opencv.hpp"
#include "iostream"
Graph::Graph(int minValue, 
            int maxValue, 
            unsigned int width, 
            unsigned int height,
			unsigned int numberOfValues,
			std::string imageName)
{
	this->minValue = minValue;
	this->maxValue = maxValue;
	this->width = width;
	this->heigth = height;
	this->numberOfValues = numberOfValues;
	this->imageName = imageName;
	this->image = new cv::Mat(height, width, CV_8UC1);
	cv::namedWindow(this->imageName);
	cv::imshow(imageName, *this->image);
	for(uint i = 0; i < this->numberOfValues; i ++)
	{
		this->values.push_back(0);
	}
}

void Graph::display()
{
	ulong average = 0;
	std::list<uint>::iterator iter = this->values.begin();
	uint currentValueId = 0;
	uint numberOfValusForCol;
	
	for(uint col = 0; col < this->width; col++)
	{
		average = 0;
		numberOfValusForCol = 0;
		while(iter != this->values.end() && 
			currentValueId * this->width / this->numberOfValues <= col)
		{
			average += *iter;
			*iter++;
			numberOfValusForCol ++;
			currentValueId ++;
		}	
		average /= numberOfValusForCol;
		for(uint row = 0; row < this->heigth; row ++)
		{
			if(this->heigth - row < average * this->heigth / this->maxValue)
			{
				this->image->at<uchar>(row, col) = 255;
			}
			else
			{
				this->image->at<uchar>(row, col) = 0;
			}
		}
	}
	cv::imshow(imageName, *image);
	
}

void Graph::updateValues(uint* values, uint numberOfValues)
{
	for(uint i = 0; i < numberOfValues; i++)
	{
		this->updateValue(values[i]);			
	}
}

void Graph::updateValue(uint value)
{
	this->values.push_back(value);
	this->values.pop_front();
}

void Graph::setValueRange(uint minValue, uint maxValue)
{
	this->minValue = minValue;
	this->maxValue = maxValue;
}

Graph::~Graph()
{
}

