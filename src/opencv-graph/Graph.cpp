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
	for(unsigned int i = 0; i < this->numberOfValues; i ++)
	{
		this->values.push_back(0);
	}
}

void Graph::display()
{
	unsigned long average = 0;
	unsigned int currentValueId = 0;
	unsigned int numberOfValusForCol;
	this->myMutex.lock();
	std::list<unsigned int>::iterator iter = this->values.begin();
	
	for(unsigned int col = 0; col < this->width; col++)
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
		for(unsigned int row = 0; row < this->heigth; row ++)
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
	this->myMutex.unlock();
	cv::imshow(imageName, *image);
	
}

void Graph::updateValues(unsigned int* values, unsigned int numberOfValues)
{
	this->myMutex.lock();
	for(unsigned int i = 0; i < numberOfValues; i++)
	{
		this->updateValuePr(values[i]);			
	}
	this->myMutex.unlock();
}

void Graph::updateValue(unsigned int value)
{
	this->myMutex.lock();
	this->updateValuePr(value);
	this->myMutex.unlock();
}

void Graph::updateValuePr(unsigned int value)
{
	this->values.push_back(value);
	this->values.pop_front();
}

void Graph::setValueRange(unsigned int minValue, unsigned int maxValue)
{
	this->minValue = minValue;
	this->maxValue = maxValue;
}

Graph::~Graph()
{
}

