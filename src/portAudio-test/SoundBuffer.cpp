/* 
 * File:   SoundBuffer.cpp
 * Author: christian
 * 
 * Created on 12. Mai 2014, 15:40
 */

#include "SoundBuffer.h"
#include <iostream>

SoundBuffer::SoundBuffer(int seconds, double sampleRate, Graph* graph)
{
	this->numberOfSamples = seconds * sampleRate;
	this->buffer = new SAMPLE[this->numberOfSamples];
	this->endBuffer = this->buffer + this->numberOfSamples;
	this->readBuffer = this->buffer;
	this->writeBuffer = this->buffer;
	this->graph = graph;
}

/*
 * buffer: stelle zum hinschreiben
 */
unsigned long SoundBuffer::read(SAMPLE* buffer, unsigned long numberOfSamples)
{
	myMutex.lock();
	if(numberOfSamples > this->calcValuesToRead()){
		numberOfSamples = this->calcValuesToRead();
	}
	for (int i = 0; i < numberOfSamples ; i++){
		if (buffer != NULL)
		{
			*buffer = *this->readBuffer;
		}
		this->readBuffer++;
		*buffer++;
		if (this->readBuffer == this->endBuffer)
		{
			this->readBuffer = this->buffer;
		}
	}
	myMutex.unlock();
	return numberOfSamples;
	
}
unsigned long SoundBuffer::write(const SAMPLE* buffer, unsigned long numberOfSamples)
{
	myMutex.lock();
	if(numberOfSamples > this->calcValuesToWrite()){
		numberOfSamples = this->calcValuesToWrite();
	}
	for (int i = 0; i < numberOfSamples ; i++){
		*this->writeBuffer = *buffer;
		if (graph != NULL)
		{
			graph->updateValue((uint)(*buffer * 1000 + 128));
		}
		this->writeBuffer++;
		buffer++;
		if (this->writeBuffer == this->endBuffer)
		{
			this->writeBuffer = this->buffer;
		}
	}
	myMutex.unlock();
	return numberOfSamples;
}

unsigned long SoundBuffer::calcValuesToWrite()
{
	if (writeBuffer < readBuffer)
	{
		return readBuffer - writeBuffer -1;
	} 
	else 
	{
		return this->endBuffer - this->writeBuffer + this->readBuffer - this->buffer - 1;
	}
}

unsigned long SoundBuffer::calcValuesToRead()
{
	if(this->readBuffer <= this->writeBuffer) {
		return this->writeBuffer - this->readBuffer;
	}
	else
	{
		return this->endBuffer - this->readBuffer + this->writeBuffer - this->buffer + 1;
	}
}

void SoundBuffer::makeCalculations(SAMPLE* min, SAMPLE* max, double* average)
{
	unsigned long numberOfValues = this->calcValuesToRead();
	SAMPLE* ptr = this->readBuffer;
	*average = 0;
	*max = 0;
	SAMPLE value;
	for (int i = 0; i < numberOfValues ; i++){
		value = *ptr;
		if (value > *max) *max = value;
		if (value < *min) *min = value;
		
		if (value < 0) value = - value;
		if (value > *max) *max = value;
		*average += value;
		ptr++;
		if (ptr == this->endBuffer)
		{
			ptr = this->buffer;
		}
	}
	*average /= numberOfValues;
}

SoundBuffer::~SoundBuffer()
{
	delete(this->buffer);
}

