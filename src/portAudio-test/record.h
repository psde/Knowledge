#ifndef _record_h_
#define _record_h_

#include <portaudio.h>

#include "SoundBuffer.h"

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define DEFAULT_SAMPLE_RATE  (48000)
//#define DEFAULT_SAMPLE_RATE  (44100)


/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

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

int recordPlayback(PaDeviceIndex inputDevice, PaDeviceIndex outputDevice);

class Recorder{
private:
    PaDeviceIndex deviceIndex;
    const PaDeviceInfo* deviceInfo;
    int channels;
    double sampleRate;
    PaStream*           stream;
    PaError             err = paNoError;
    
    SoundBuffer* buffer;
    
public:    
    Recorder(PaDeviceIndex device, SoundBuffer* buffer);
    bool isRecording();
    void makeAfterRecordCalculations();
    int record();
};


#endif // _record_h_