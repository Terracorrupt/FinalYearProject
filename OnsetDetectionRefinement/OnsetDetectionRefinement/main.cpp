#include "FMODSetup.h"
#include <algorithm>
#include <queue>
#include <Windows.h>
#include <array>
#include <math.h>

int main()
{
	FMOD::System *system;
	FMOD_RESULT result;

	system = fmodSetup();

	int sampleSize = 1024;
	int test;
	float sampleRate;
	unsigned int seconds;
	unsigned int minutes;
	bool areWePlaying = true;
	float* previousFFT;
	float specFlux=0.0;
	float difference;

	FMOD::Sound *audio;
	FMOD::ChannelGroup *channelMusic;
	FMOD::Channel *songChannel1;

	FMODErrorCheck(system->createChannelGroup(NULL, &channelMusic));
	FMODErrorCheck(system->createSound("Sound/cochice.mp3", FMOD_SOFTWARE, 0, &audio));

	audio->getLength(&seconds, FMOD_TIMEUNIT_MS);
	audio->getDefaults(&sampleRate, 0, 0, 0);
	seconds = ((seconds + 500) / 1000);

	minutes = seconds / 60;
	seconds = seconds - (minutes * 60);

	FMODErrorCheck(system->playSound(FMOD_CHANNEL_FREE, audio, true, &songChannel1));


	songChannel1->setChannelGroup(channelMusic);
	songChannel1->setPaused(false);

	float hzRange = (44100 / 2) / static_cast<float>(sampleSize);

	std::vector<float> spectrumFluxes;

	std::cout << "Song Length: " << minutes << ":" << seconds << std::endl;
	std::cout << "Sample Rate: " << sampleRate << std::endl;
	std::cout << "Freq Range: " << hzRange << std::endl;

	previousFFT = new float[sampleSize / 2+1];

	for (int i = 0; i < sampleSize / 2; i++)
	{
		previousFFT[i] = 0;
	}

	while (areWePlaying)
	{

		specFlux = 0.0;
		float *specLeft, *specRight, *specStereo;

		specLeft = new float[sampleSize];
		specRight = new float[sampleSize];
		specStereo = new float[sampleSize/2+1];

		//Get Spectrum of Song Channel for left and right
		songChannel1->getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_HAMMING);
		songChannel1->getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_HAMMING);

		//Average spectrum for stereo song channel, Divided by 2 cause Nyquist
		for (int i = 0; i < sampleSize/2; i++)
		{
			specStereo[i] = (specLeft[i] + specRight[i]);
			//std::cout << specStereo[i] << std::endl;
		}

		//Calculate differences
		for (int i = 0; i < sampleSize/2; i++)
		{
			difference = specStereo[i] - previousFFT[i];

			if (difference > 0) {
				specFlux += difference;
			}

			spectrumFluxes.push_back(specFlux);

			if (spectrumFluxes.size()>15)			{				spectrumFluxes.erase(spectrumFluxes.begin());			}
		}

		//Accuracy
		/*for (int i = 0; i < thresholdValues.size(); i++)
		{
			if (thresholdValues.at(i) <= spectrumFluxes.at(i))
				accurateSpectrumFluxes.push_back(spectrumFluxes.at(i) - thresholdValues.at(i));
			else
				accurateSpectrumFluxes.push_back((float)0);
		}*/

		specFlux /= sampleSize / 2;

		for (int j = 0; j < sampleSize / 2; j++)
			previousFFT[j] = specStereo[j];

		if (specFlux > 0.001)
			//std::cout << specStereo[0] << std::endl;

			//std::cout << specFlux << std::endl;

		songChannel1->isPlaying(&areWePlaying);

		
		// Memory management
		delete[] specStereo;
		delete[] specLeft;
		delete[] specRight;
	}


	std::cin >> test;

}