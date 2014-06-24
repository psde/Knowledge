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

class SoundBuffer {
    SAMPLE* buffer;
    SAMPLE* readBuffer;
    SAMPLE* writeBuffer;
    SAMPLE* endBuffer;
    unsigned long numberOfSamples;
    unsigned long calcValuesToWrite();
    unsigned long calcValuesToRead();
    std::mutex myMutex;
public:
    SoundBuffer(int seconds, double sampleRate);
    unsigned long read(SAMPLE* buffer, unsigned long numberOfSamples);
    unsigned long write(const SAMPLE* buffer, unsigned long numberOfSamples);
    void makeCalculations(SAMPLE* min, SAMPLE* max, double* average);
    virtual ~SoundBuffer();
private:

};

#endif	/* SOUNDBUFFER_H */

