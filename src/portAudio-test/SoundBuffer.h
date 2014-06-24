/* 
 * File:   SoundBuffer.h
 * Author: christian
 *
 * Created on 12. Mai 2014, 15:40
 */

#ifndef SOUNDBUFFER_H
#define	SOUNDBUFFER_H

#include "defines.h"
#define __cplusplus  201103L
#include <mutex>

/** 
 * Ringpuffer zur Verwaltung von Audiodaten
 */
class SoundBuffer
{
	SAMPLE* buffer;
	SAMPLE* readBuffer;
	SAMPLE* writeBuffer;
	SAMPLE* endBuffer;
	unsigned long numberOfSamples;
	unsigned long calcValuesToWrite();
	unsigned long calcValuesToRead();
	std::mutex myMutex;
public:
	/**
	 * 
	 * @param seconds Anzahl der Sekunden, die gepuffert werden sollen
	 * @param sampleRate Anzahl der Samples pro Sekunde
	 */
	SoundBuffer(int seconds, double sampleRate);
	/**
	 * 
	 * @param buffer Puffer, in den Werte geschrieben werden sollen
	 * @param numberOfSamples Anzahl der Samples, die in den Puffer passen
	 * @return anzahl der gelesenen Samples
	 */
	unsigned long read(SAMPLE* buffer, unsigned long numberOfSamples);
	/**
	 * 
     * @param buffer Puffer, aus dem Werte gelesen werden sollen
     * @param numberOfSamples Anzahl der Samples, die im Puffer stehen
     * @return anzahl der Samples, die aus dem Puffer gelesen wurden
     */
	unsigned long write(const SAMPLE* buffer, unsigned long numberOfSamples);
	/**
	 * 
     * @param min out: min Value in Puffer
     * @param max out: may Value in Puffer
     * @param average out: average Value in Puffer
     */
	void makeCalculations(SAMPLE* min, SAMPLE* max, double* average);
	virtual ~SoundBuffer();

};

#endif	/* SOUNDBUFFER_H */

