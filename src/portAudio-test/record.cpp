#include "record.h"
#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>
#include <iostream>
#include "SoundBuffer.h"

/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
static int recordCallback(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData)
{
	SoundBuffer* buffer = (SoundBuffer*) userData;
	const SAMPLE *rptr = (const SAMPLE*) inputBuffer;
	
	(void) outputBuffer; /* Prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;
	(void) userData;
	PaStreamCallbackResult finished;
	
	//std::cout << timeInfo->inputBufferAdcTime << " " << framesPerBuffer <<  std::endl;
	if (buffer->write(rptr, framesPerBuffer) != framesPerBuffer) {
		finished = paComplete;
	}
	else
	{
		finished = paContinue;
	}
	return finished;
}

/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
int playCallback(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData)
{
	SoundBuffer *buffer = (SoundBuffer*) userData;
	PaStreamCallbackResult finished;
	SAMPLE *wptr = (SAMPLE*) outputBuffer;
	if (buffer->read(wptr, framesPerBuffer)!= framesPerBuffer)
	{
		finished = paComplete;
	}
	else
	{
		finished = paContinue;
	}
	return finished;
}

/*******************************************************************/

/*
int recordPlayback(PaDeviceIndex inputDevice, PaDeviceIndex outputDevice)
{
	PaStreamParameters inputParameters,
			outputParameters;
	PaStream* stream;
	PaError err = paNoError;
	paData data;
	int i;
	int totalFrames;
	int numSamples;
	int numBytes;
	SAMPLE max, val;
	double average;

	printf("patest_record.c\n");
	fflush(stdout);

	data.maxFrameIndex = totalFrames = NUM_SECONDS * DEFAULT_SAMPLE_RATE;
	// Record for a few seconds. 
	data.frameIndex = 0;
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);
	data.recordedSamples = (SAMPLE *) malloc(numBytes); // From now on, recordedSamples is initialised. 
	if (data.recordedSamples == NULL) {
		printf("Could not allocate record array.\n");
		goto done;
	}
	for (i = 0; i < numSamples; i++) data.recordedSamples[i] = 0;

	err = Pa_Initialize();
	if (err != paNoError) goto done;

	//PaDeviceIndex test = Pa_GetDeviceCount();
	const PaDeviceInfo *deviceInfo;
	deviceInfo = Pa_GetDeviceInfo(2);
	inputParameters.device = inputDevice; // Pa_GetDefaultInputDevice(); // default input device 
	if (inputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default input device.\n");
		goto done;
	}
	inputParameters.channelCount = 2; // stereo input 
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	// Record some audio. -------------------------------------------- 
	err = Pa_OpenStream(
			&stream,
			&inputParameters,
			NULL, // &outputParameters, 
			DEFAULT_SAMPLE_RATE,
			DEFAULT_FRAMES_PER_BUFFER,
			paClipOff, // we won't output out of range samples so don't bother clipping them 
			recordCallback,
			&data);
	if (err != paNoError) goto done;

	err = Pa_StartStream(stream);
	if (err != paNoError) goto done;
	printf("\n=== Now recording!! Please speak into the microphone. ===\n");
	fflush(stdout);

	while ((err = Pa_IsStreamActive(stream)) == 1) {
		Pa_Sleep(1000);
		printf("index = %d\n", data.frameIndex);
		fflush(stdout);
	}
	if (err < 0) goto done;

	err = Pa_CloseStream(stream);
	if (err != paNoError) goto done;

	// Measure maximum peak amplitude. 
	max = 0;
	average = 0.0;
	for (i = 0; i < numSamples; i++) {
		val = data.recordedSamples[i];
		if (val < 0) val = -val; // ABS 
		if (val > max) {
			max = val;
		}
		average += val;
	}

	average = average / (double) numSamples;

	printf("sample max amplitude = "PRINTF_S_FORMAT"\n", max);
	printf("sample average = %lf\n", average);

	// Write recorded data to a file. 
#if WRITE_TO_FILE
	{
		FILE *fid;
		fid = fopen("recorded.raw", "wb");
		if (fid == NULL) {
			printf("Could not open file.");
		} else {
			fwrite(data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalFrames, fid);
			fclose(fid);
			printf("Wrote data to 'recorded.raw'\n");
		}
	}
#endif

	// Playback recorded data.  -------------------------------------------- 
	data.frameIndex = 0;
	outputParameters.device = outputDevice; // Pa_GetDefaultOutputDevice(); // default output device 
	if (outputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default output device.\n");
		goto done;
	}
	outputParameters.channelCount = 2; // stereo output 
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	printf("\n=== Now playing back. ===\n");
	fflush(stdout);
	err = Pa_OpenStream(
			&stream,
			NULL, // no input 
			&outputParameters,
			DEFAULT_SAMPLE_RATE,
			DEFAULT_FRAMES_PER_BUFFER,
			paClipOff, // we won't output out of range samples so don't bother clipping them 
			playCallback,
			&data);
	if (err != paNoError) goto done;

	if (stream) {
		err = Pa_StartStream(stream);
		if (err != paNoError) goto done;

		printf("Waiting for playback to finish.\n");
		fflush(stdout);

		while ((err = Pa_IsStreamActive(stream)) == 1) Pa_Sleep(100);
		if (err < 0) goto done;

		err = Pa_CloseStream(stream);
		if (err != paNoError) goto done;

		printf("Done.\n");
		fflush(stdout);
	}

done:
	Pa_Terminate();
	if (data.recordedSamples) // Sure it is NULL or valid. 
		free(data.recordedSamples);
	if (err != paNoError) {
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1; // Always return 0 or 1, but no other return codes. 
	}
	return err;
}
 */
Recorder::Recorder(PaDeviceIndex device, SoundBuffer* buffer)
{
	this->deviceIndex = device;
	this->deviceInfo = Pa_GetDeviceInfo(this->deviceIndex);
	this->channels = this->deviceInfo->maxInputChannels;
	this->sampleRate = DEFAULT_SAMPLE_RATE;
	this->buffer = buffer;

}

/*******************************************************************/
int Recorder::record()
{

	err = Pa_Initialize();
	if (err != paNoError) goto done;

	PaStreamParameters inputParameters;
	inputParameters.device = this->deviceIndex;
	inputParameters.channelCount = this->channels;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = this->deviceInfo->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;


	/* Record some audio. -------------------------------------------- */
	err = Pa_OpenStream(
			&this->stream,
			&inputParameters,
			NULL, /* &outputParameters, */
			this->sampleRate,
			4800, // 0 as recommended by PortAudio
			paClipOff, /* we won't output out of range samples so don't bother clipping them */
			recordCallback,
			buffer);
	if (err != paNoError) goto done;

	err = Pa_StartStream(this->stream);
	if (err != paNoError) goto done;
	printf("\n=== Now recording!! Please speak into the microphone. ===\n");
	fflush(stdout);

	/* Write recorded data to a file. */
#if WRITE_TO_FILE
	{
		FILE *fid;
		fid = fopen("recorded.raw", "wb");
		if (fid == NULL) {
			printf("Could not open file.");
		} else {
			fwrite(data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalFrames, fid);
			fclose(fid);
			printf("Wrote data to 'recorded.raw'\n");
		}
	}
#endif

done:
	Pa_Terminate();
//	if (data.recordedSamples) /* Sure it is NULL or valid. */
//		free(data.recordedSamples);
	if (err != paNoError) {
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		err = 1; /* Always return 0 or 1, but no other return codes. */
	}
	return err;
}

void Recorder::makeAfterRecordCalculations()
{
	if (!isRecording()) {

		SAMPLE max, min;
		double average;
		this->buffer->makeCalculations(&min, &max, &average);
		printf("sample max amplitude = "PRINTF_S_FORMAT"\n", max);
		printf("sample min amplitude = "PRINTF_S_FORMAT"\n", min);
		printf("sample average = %lf\n", average);

	}
}

bool Recorder::isRecording()
{
	return Pa_IsStreamActive(stream) > 0;
}

