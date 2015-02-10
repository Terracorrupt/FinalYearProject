#include "FMODSetup.h"
#include <algorithm>
#include <queue>
#include <Windows.h>
#include <array>
#include <math.h>

void quickSort(std::vector<float>& a, int l, int r);
int partition(std::vector<float>& a, int l, int r);

int main()
{
	FMOD::System *system;
	FMOD_RESULT result;

	system = fmodSetup();

	int sampleSize = 1024;
	int test;
	float volume;
	float sampleRate;
	unsigned int seconds;
	unsigned int minutes;
	bool areWePlaying = true;
	float* previousFFT;
	float specFlux=0.0;
	float difference;
	unsigned int timeBetween = 0;

	FMOD::Sound *audio;
	FMOD::ChannelGroup *channelMusic;
	FMOD::Channel *songChannel1;

	DWORD initialTime = GetTickCount();
	DWORD currentTime = 0;
	DWORD currentMillis = 0;
	DWORD currentSeconds = 0;
	DWORD currentMinutes = 0;

	FMODErrorCheck(system->createChannelGroup(NULL, &channelMusic));
	FMODErrorCheck(system->createSound("Sound/gangam.mp3", FMOD_SOFTWARE, 0, &audio));

	audio->getLength(&seconds, FMOD_TIMEUNIT_MS);
	audio->getDefaults(&sampleRate, &volume, 0, 0);
	seconds = ((seconds + 500) / 1000);
	minutes = seconds / 60;
	seconds = seconds - (minutes * 60);

	FMODErrorCheck(system->playSound(FMOD_CHANNEL_FREE, audio, true, &songChannel1));


	songChannel1->setChannelGroup(channelMusic);
	songChannel1->setPaused(false);

	float hzRange = (44100 / 2) / static_cast<float>(sampleSize);

	std::vector<float> spectrumFluxes;
	std::vector<float> smootherValues;
	float median = 0.0;
	float smoothMedian = 0.0;
	float beatThreshold = 0.6f;
	float thresholdSmoother = 0.6f;

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

		//Get Time
		currentTime = GetTickCount();
		currentTime = currentTime - initialTime;

		if (currentMinutes>0)
			currentSeconds = ((currentTime / 1000) - (60*currentMinutes));
		else
			currentSeconds = (currentTime / 1000);

		currentMinutes = ((currentTime / 1000) / 60);



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
		}

		//specFlux /= (sampleSize / 2 + 1);

		//Get our median for threshold
		if (spectrumFluxes.size() > 0 && spectrumFluxes.size()<10)
		{
			std::sort(spectrumFluxes.begin(), spectrumFluxes.end());
			//quickSort(spectrumFluxes, 0, spectrumFluxes.size() - 1);
			std::sort(smootherValues.begin(), smootherValues.end());

			if (spectrumFluxes.at(spectrumFluxes.size() / 2) > 0)
			{
				median = spectrumFluxes.at(spectrumFluxes.size() / 2);
			}

			if (smootherValues.size() > 0 && smootherValues.size() < 5)
			{

				if (smootherValues.at(smootherValues.size() / 2) > 0)
				{
					smoothMedian = smootherValues.at(smootherValues.size() / 2);
				}
			}
			//std::cout << median << std::endl;
		}

		//Copy spectrum for next spectral flux calculation
		for (int j = 0; j < sampleSize / 2; j++)
			previousFFT[j] = specStereo[j];


		if (smoothMedian > 1)
			thresholdSmoother = 0.8f;
		if (smoothMedian > 2 && smoothMedian < 4)
			thresholdSmoother = 1.0f;
		if (smoothMedian > 4 && smoothMedian < 6)
			thresholdSmoother = 2.5f;
		if (smoothMedian > 6)
			thresholdSmoother = 2.9f;

		//Calculate our adaptive threshold
		beatThreshold = thresholdSmoother + median;
		
		//std::cout << specFlux << std::endl;
		//Beat detected
		if (specFlux > beatThreshold && (GetTickCount()-timeBetween)>350)
		{
			smootherValues.push_back(specFlux);

			if (smootherValues.size() >= 5)
			{
				smootherValues.erase(smootherValues.begin());
			}

			timeBetween = GetTickCount();
			std::cout  << "BEAT AT: "<< currentMinutes << ":" << currentSeconds  << " -- BEAT FREQ: " << specFlux << " -- THRESHOLD:" << beatThreshold << std::endl;
		}

		
		for (int i = 0; i < sampleSize / 2; i++)
		{
			spectrumFluxes.push_back(specFlux);

			if (spectrumFluxes.size()>=10)
			{
				spectrumFluxes.erase(spectrumFluxes.begin());
			}
		}

		songChannel1->isPlaying(&areWePlaying);

		// Memory management
		delete[] specStereo;
		delete[] specLeft;
		delete[] specRight;
	}


	std::cin >> test;

}

void quickSort(std::vector<float>& unsorted, int l, int r)
{
	int j;

	if (l < r)
	{
		j = partition(unsorted, l, r);
		quickSort(unsorted, l, j - 1);
		quickSort(unsorted, j + 1, r);
	}

}



int partition(std::vector<float>& passedIn, int l, int r) 
{
	float pivot;
	float t;
	int i, j;
	pivot = passedIn.at(l);
	i = l; j = r - 1;

	while (1)
	{
		
		while (i <= r && passedIn.at(i) <= pivot)
		{
			i++;
		}
		while (passedIn.at(j) > pivot)
		{
			j--;
		}
		if (i >= j) break;

		t = passedIn.at(i); passedIn.at(i) = passedIn.at(j); passedIn.at(j) = t;
	}
	t = passedIn.at(l); passedIn.at(l) = passedIn.at(j); passedIn.at(j) = t;
	return j;
}