#include "FMODSetup.h"
#include <algorithm>
#include <queue>
#include <Windows.h>
#include <array>
#include <math.h>

void hamming(float* samples);

int main()
{
	FMOD::System *system;
	FMOD_RESULT result;
	int test;
	int sampleSize = 64;
	float sampleRate;
	unsigned int seconds;
	unsigned int minutes;

	//BEAT DETECTION TESTS
	// Set beat detection parameters
	float beatThresholdVolume = 0.3f;
	int beatThresholdBar = 0;
	unsigned int beatSustain = 150;
	unsigned int beatPostIgnore = 250;
	unsigned int beatTrackCutoff = 10000;

	std::queue<int> beatTimes;
	int beatLastTick = 0;
	int beatIgnoreLastTick = 0;

	int musicStartTick = 0;
	bool beatDetected = false;

	

	//Get System Pointer from setup
	system = fmodSetup();

	FMOD::Sound *audio;
	FMOD::ChannelGroup *channelMusic;
	FMOD::Channel *songChannel1;

	FMODErrorCheck(system->createChannelGroup(NULL, &channelMusic));
	FMODErrorCheck(system->createSound("Music/SK1.mp3", FMOD_SOFTWARE, 0, &audio));

	audio->getLength(&seconds, FMOD_TIMEUNIT_MS);
	audio->getDefaults(&sampleRate, 0,0,0);
	seconds = ((seconds + 500) / 1000);
	minutes = seconds / 60;
	seconds = seconds - (minutes * 60);

	FMODErrorCheck(system->playSound(FMOD_CHANNEL_FREE, audio, true, &songChannel1));

	songChannel1->setChannelGroup(channelMusic);
	songChannel1->setPaused(false);

	float hzRange = (44100 / 2) / static_cast<float>(sampleSize);

	std::cout << "Song Length: " << minutes << ":" << seconds << std::endl;
	std::cout << "Sample Rate: " << sampleRate << std::endl;
	std::cout << "Freq Range: " << hzRange << std::endl;

	bool beatOccured = false;

	while (system->update() == FMOD_OK)
	{
		system->update();

		float *specLeft, *specRight, *specStereo;

		specLeft = new float[sampleSize];
		specRight = new float[sampleSize];
		specStereo = new float[sampleSize];

		//Get Spectrum of Song Channel for left and right
		songChannel1->getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_HAMMING);
		songChannel1->getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_HAMMING);

		//Average spectrum for stereo song channel, Divided by 2 cause Nyquist
		for (int i = 0; i < sampleSize/2; i++)
		{
			specStereo[i] = (specLeft[i] + specRight[i]);
			//std::cout << specStereo[i] << std::endl;
		}

		//songChannel1->setVolume(0.2);

		//If current spectrum is greater than or equal to the threshold (.300 ) and we've finished ignoring, a beat has occured 
		if (specStereo[beatThresholdBar] >= beatThresholdVolume && beatLastTick == 0 && beatIgnoreLastTick == 0)
		{
			beatLastTick = GetTickCount();
			beatTimes.push(beatLastTick);

			while (GetTickCount() - beatTimes.front() > beatTrackCutoff)
			{
				beatTimes.pop();
				if (beatTimes.size() == 0)
					break;
			}

			beatOccured = true;
		}

		if (GetTickCount() - beatLastTick < beatSustain && beatOccured)
		{
			std::cout << "BEAT AT VOL: " << specStereo[beatThresholdBar] << std::endl;
			beatOccured = false;
		}
		else if (beatIgnoreLastTick == 0 && beatLastTick != 0)
		{
			beatLastTick = 0;
			beatIgnoreLastTick = GetTickCount();
		}

		if (GetTickCount() - beatIgnoreLastTick >= beatPostIgnore)
			beatIgnoreLastTick = 0;

		// Predict BPM
		float msPerBeat, bpmEstimate;

		if (beatTimes.size() >= 2)
		{
			msPerBeat = (beatTimes.back() - beatTimes.front()) / static_cast<float>(beatTimes.size() - 1);
			bpmEstimate = 60000 / msPerBeat;
		}
		else
			bpmEstimate = 0;

		//std::cout << bpmEstimate << std::endl;
		// Memory management
		delete[] specStereo;
		delete[] specLeft;
		delete[] specRight;
	}

	std::cin >> test;
}