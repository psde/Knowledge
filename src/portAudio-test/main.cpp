
//#include "sine.h"
#include "record.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include "split.h"
#include <opencv2/opencv.hpp>
#include "../opencv-graph/Graph.h"
/*******************************************************************/
int main(void);
using namespace std;


string getDate()
{
	time_t Zeitstempel;
    tm *nun;
    Zeitstempel = time(0);
    nun = localtime(&Zeitstempel);
    stringstream bla;
	bla << nun->tm_year + 1900 -2000;
	if (nun->tm_mon + 1 < 10) bla << 0;
	bla << nun->tm_mon + 1;
	if (nun->tm_mday < 10) bla << 0;
	bla << nun->tm_mday;
	bla << "_";
	if (nun->tm_hour < 10) bla << 0;
	bla << nun->tm_hour;
	if (nun->tm_min < 10) bla << 0;
	bla << nun->tm_min;
	if (nun->tm_sec < 10) bla << 0;
	bla << nun->tm_sec;
	return bla.str();
}

int main(void)
{
	int err = Pa_Initialize();
	ofstream myfile;
	myfile.open (getDate());
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
		deviceInfo = inputDevices[id].second;
		cout << id << ": " << deviceInfo->name << endl;
		graph[i] = new Graph(0, 400, 1000, 200, 1000, "Image");
		buffer[i] = new SoundBuffer(5, deviceInfo->defaultSampleRate);
		recorder[i] = new Recorder(inputDevices[id].first, buffer[i]);
	}
	
	myfile << inputDevices[atoi(selectedInputDevices[0].c_str())].first << ": ";
	myfile << inputDevices[atoi(selectedInputDevices[0].c_str())].second->name << endl;
	
  recorder[0]->record();
  SAMPLE* tmp = new SAMPLE[1000];
  SAMPLE avg; 
  SAMPLE bigAvg;
  uint countForBigAvg = 100;
  while (recorder[0]->isRecording()) {
	  bigAvg = 0;
        for(uint i = 0; i < countForBigAvg; i ++)
		{
			Pa_Sleep(10);
			for(uint i = 0; i <	selectedInputDevices.size(); i++)
			{
				avg = 0;
				int max = buffer[i]->read(tmp, 1000);
				for(uint i = 0; i < max; i ++)
				{
					avg+= ((tmp[i] > 0) ? tmp[i] : -tmp[i] / max);
				}
				graph[i]->updateValue(avg * 100);
				std::cout << max << " " << avg << endl;

				graph[i]->display();

			}
			bigAvg += avg;
			cv::waitKey(1);
		}
		bigAvg /= countForBigAvg;
		myfile << getDate() << ": " << bigAvg << endl;
		
  }
  
  recorder[0]->makeAfterRecordCalculations();

    //recordPlayback(0, 4);
	//return sine(2);
  myfile.close();
	
	return err;
}
