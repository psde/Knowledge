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
    int numberOfSamples;
    int calcValuesToWrite();
    int calcValuesToRead();
    std::mutex myMutex;
public:
    SoundBuffer(int seconds, double sampleRate);
    int read(SAMPLE* buffer,  int numberOfSamples);
    int write(const SAMPLE* buffer, int numberOfSamples);
    virtual ~SoundBuffer();
private:

};

#endif	/* SOUNDBUFFER_H */

