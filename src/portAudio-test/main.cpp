
//#include "sine.h"
#include "record.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "split.h"
#include <opencv2/opencv.hpp>
/*******************************************************************/
int main(void);
using namespace std;



/*int sine(PaDeviceIndex device){

	PaError err;
	Sine sine;


	printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);


	if (sine.open(device))//Pa_GetDefaultOutputDevice()))
	{
		if (sine.start())
		{
			printf("Play for %d seconds.\n", NUM_SECONDS);
			Pa_Sleep(NUM_SECONDS * 1000);

			sine.stop();
		}

		sine.close();
	}

	Pa_Terminate();
	printf("Test finished.\n");

	return err;

error:
	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
	return err;


}*/

int main(void)
{
	int err = Pa_Initialize();

	const PaDeviceInfo* deviceInfo;
	int deviceCount = Pa_GetDeviceCount();
  if (deviceCount < 0) {
      //TODO: Error
      return deviceCount;
  }
  
	cout << deviceCount << " Audiogeräte gefunden." << endl;
	
	vector<pair<int, const PaDeviceInfo*> > inputDevices;
	vector<pair<int, const PaDeviceInfo*> > outputDevices;
	for (int i = 0; i < Pa_GetDeviceCount(); i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		if (deviceInfo->maxInputChannels > 0)
		{
			inputDevices.push_back(pair<int, const PaDeviceInfo*>(i, deviceInfo));
		}
		if (deviceInfo->maxOutputChannels > 0)
		{
			outputDevices.push_back(pair<int, const PaDeviceInfo*>(i, deviceInfo));
		}
	}
	
	for(int i = 0; i < inputDevices.size(); i++) 
	{
		cout << i << ": " << inputDevices[i].second->name << endl;
	}
	
	string selcted;
	cout << "select input devices (seperated by ,)" << endl;
	cin >> selcted;
	vector<string> selectedInputDevices;
	split(selectedInputDevices, selcted, ",");

	for(int i = 0; i < outputDevices.size(); i++) 
	{
		cout << i << ": " << outputDevices[i].second->name << endl;
	}

	
	cout << "select output devices (seperated by ,)" << endl;
	cin >> selcted;
	vector<string> selectedOutputDevices;
	split(selectedOutputDevices, selcted, ",");
	
	Recorder* recorder[selectedInputDevices.size()];
	SoundBuffer* buffer[selectedInputDevices.size()];
	Graph* graph[selectedInputDevices.size()];
	for (int i = 0; i < selectedInputDevices.size(); i++)
	{
		int id = atoi(selectedInputDevices[i].c_str());
		deviceInfo = Pa_GetDeviceInfo(id);
		cout << i << ": " << deviceInfo->name << endl;
		graph[i] = new Graph(0, 255, 1000, 200, 50000, "Image");
		buffer[i] = new SoundBuffer(5, deviceInfo->defaultSampleRate, graph[i]);
		recorder[i] = new Recorder(id, buffer[i]);
	}
	
	
  recorder[0]->record();

  while (recorder[0]->isRecording()) {
        Pa_Sleep(10);
		for(uint i = 0; i <	selectedInputDevices.size(); i++)
		{
			graph[i]->display();
			buffer[i]->read(NULL, 1000);
		}
		
		cv::waitKey(1);
  }
  
  recorder[0]->makeAfterRecordCalculations();

    //recordPlayback(0, 4);
	//return sine(2);
	return err;
}
