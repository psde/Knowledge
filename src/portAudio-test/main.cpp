
//#include "sine.h"
#include "record.h"
#include <iostream>
#include <string.h>
#include <vector>
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
	vector<int> inputDevices;
  for (int i = 0; i < Pa_GetDeviceCount(); i++){
		deviceInfo = Pa_GetDeviceInfo(i);
    if (strstr(deviceInfo->name, "0x46d:0x809"))
    {
        inputDevices.push_back(i);
    }
	}
    Recorder* recorder[inputDevices.size()];
	{
		int i = 0;
		for(vector<int>::iterator itr = inputDevices.begin();itr != inputDevices.end() ; itr ++ , i++)
		{
			deviceInfo = Pa_GetDeviceInfo(*itr);  
			cout << *itr << " " << deviceInfo->name << endl;
			recorder[i] = new Recorder(*itr);
		}
	}
  cout << inputDevices.size() << " davon vom Typ 0x46d:0x809." << endl;


  recorder[0]->record(5);

  while (recorder[0]->isRecording()) {
        Pa_Sleep(1000);
  }
  
  recorder[0]->makeAfterRecordCalculations();

  //recordPlayback(1, 4);
	//return sine(2);
	return err;
}
