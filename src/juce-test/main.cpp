#include <iostream>
#include "juce_audio_devices.h"
#include <objbase.h>

using namespace std;
using namespace juce;

int main()
{

	CoInitialize(NULL);
	AudioDeviceManager* adm = new AudioDeviceManager();
	adm->initialiseWithDefaultDevices(1, 0);
	

	cout << "Hallo Welt" << endl;
}

