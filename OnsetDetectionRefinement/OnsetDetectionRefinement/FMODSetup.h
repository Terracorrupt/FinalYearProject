#include "FMODErrorCheck.h"
#include <algorithm>
#include <queue>
#include <Windows.h>
#include <array>
#include <math.h>

#ifndef FMOD_SETUP
#define FMOD_SETUP

//FMOD::System * fmodSetup()
//{
//	FMOD::System *system;
//	FMOD_RESULT result;
//	unsigned int version;
//	int numDrivers;
//	FMOD_SPEAKERMODE speakerMode;
//	FMOD_CAPS caps;
//	char name[256];
//
//	// Create FMOD interface object
//	result = FMOD::System_Create(&system);
//	FMODErrorCheck(result);
//
//	// Check version
//	result = system->getVersion(&version);
//	FMODErrorCheck(result);
//
//	if (version < FMOD_VERSION)
//	{
//		std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;    return 0;
//	}
//
//	//Check Sound Cards, if none, disable sound
//	result = system->getNumDrivers(&numDrivers);
//	FMODErrorCheck(result);
//
//	if (numDrivers == 0)
//	{
//		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
//		FMODErrorCheck(result);
//	}
//	// At least one sound card
//	else
//	{
//		// Get the capabilities of the default (0) sound card
//		result = system->getDriverCaps(0, &caps, 0, &speakerMode);
//		FMODErrorCheck(result);
//
//		// Set the speaker mode to match that in Control Panel
//		result = system->setSpeakerMode(speakerMode);
//		FMODErrorCheck(result);
//
//		// Increase buffer size if user has Acceleration slider set to off
//		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
//		{
//			result = system->setDSPBufferSize(1024, 10);
//			FMODErrorCheck(result);
//		}
//		// Get name of driver
//		result = system->getDriverInfo(0, name, 256, 0);
//		FMODErrorCheck(result);
//
//		// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
//		// PCM floating point output seems to solve it.
//		if (strstr(name, "SigmaTel"))
//		{
//			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
//			FMODErrorCheck(result);
//		}
//	}
//
//	// Initialise FMOD
//	result = system->init(100, FMOD_INIT_NORMAL, 0);
//
//	// If the selected speaker mode isn't supported by this sound card, switch it back to stereo
//	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
//	{
//		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
//		FMODErrorCheck(result);
//
//		result = system->init(100, FMOD_INIT_NORMAL, 0);
//	}
//
//	FMODErrorCheck(result);
//
//	return system;
//};

#endif