#ifndef BEAT_DETECTOR
#define BEAT_DETECTOR

#include <algorithm>
#include <queue>
#include <Windows.h>
#include <array>
#include <math.h>
#include "fmod.hpp"
#include "fmod_errors.h"
#include "TimeStamp.h"
#include <iostream>

class BeatDetector
{
public:
	//BeatDetector(int, char*);
	void Load(int, char*);
	~BeatDetector();
	void updateTime();
	float* getCurrentSpectrum();
	float calculateFluxAndSmoothing(float*);
	void update();
	FMOD::System * fmodSetup();
	void FMODErrorCheck(FMOD_RESULT);
	void setStarted(bool);
	TimeStamp* getLastBeat();
	bool isPlaying();
	char* isLoaded();

	//Singelton
	static BeatDetector* Instance()
	{
		if (instance == 0)
		{
			instance = new BeatDetector();
		}
		return instance;
	}
	
private:
	BeatDetector(){};
	static BeatDetector* instance;
	FMOD::System *system;
	FMOD_RESULT result;
	int sampleSize;
	int test;
	float sampleRate;
	unsigned int seconds;
	unsigned int minutes;
	bool areWePlaying;
	float* previousFFT;
	float specFlux;
	float difference;
	unsigned int timeBetween;
	const char* songString;
	bool started;
	TimeStamp* lastBeatRegistered;
	char* songName;

	FMOD::Sound *audio;
	FMOD::ChannelGroup *channelMusic;
	FMOD::Channel *songChannel1;

	DWORD initialTime;
	DWORD currentTime;
	int currentMillis;
	DWORD currentSeconds;
	DWORD lastSeconds;
	DWORD currentMinutes;

	float hzRange;

	std::vector<float> spectrumFluxes;
	std::vector<float> smootherValues;
	float median;
	float smoothMedian;
	float beatThreshold;
	float thresholdSmoother;
};

#endif