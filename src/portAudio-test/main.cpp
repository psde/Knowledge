
//#include "sine.h"
#include "record.h"
#include <iostream>
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
	Pa_GetDeviceCount();
	for (int i = 0; i < Pa_GetDeviceCount(); i++){
		deviceInfo = Pa_GetDeviceInfo(i);
		cout << i << " " << deviceInfo->name << endl;
		cout << "Eingaenge: " << deviceInfo->maxInputChannels << "  Ausgaenge: " << deviceInfo->maxOutputChannels << endl;
	}
	recordPlayback(1, 4);
	//return sine(2);
	return 0;
}
