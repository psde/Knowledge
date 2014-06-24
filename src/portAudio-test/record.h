#ifndef _record_h_
#define _record_h_

#include <portaudio.h>

#include "SoundBuffer.h"
#include "defines.h"


/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
static int recordCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData);

/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
int playCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData);

class Recorder
{
private:
	PaDeviceIndex deviceIndex;
	const PaDeviceInfo* deviceInfo;
	int channels;
	double sampleRate;
	PaStream* stream;
	PaError err = paNoError;

	SoundBuffer* buffer;

public:
	Recorder(PaDeviceIndex device, SoundBuffer* buffer);
	bool isRecording();
	void makeAfterRecordCalculations();
	/**
	 * startet die Aufnahme
     * @return portAudio-ErrorCode
     */
	int record();
};


#endif // _record_h_