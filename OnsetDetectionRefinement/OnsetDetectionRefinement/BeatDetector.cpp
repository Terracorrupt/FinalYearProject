#include "BeatDetector.h"

BeatDetector* BeatDetector::instance = 0;

void BeatDetector::Load(int sSize, char* audioString)
{
	//Take in Aruguments
	sampleSize = sSize;
	songString = audioString;

	//Setup variables
	system = fmodSetup();
	areWePlaying = true;
	specFlux = 0.0f;
	timeBetween = 0;
	initialTime = GetTickCount();
	currentTime = 0;
	currentSeconds = 0;
	lastSeconds = 0;
	currentMillis = 0;
	currentMinutes = 0;
	median = 0.0f;
	smoothMedian = 0.0f;
	beatThreshold = 0.6f;
	thresholdSmoother = 0.6f;
	started = false;

	previousFFT = new float[sampleSize / 2 + 1];
	for (int i = 0; i < sampleSize / 2; i++)
	{
		previousFFT[i] = 0;
	}

	//Brute force for testing
	//songString = "Music/drums.wav";

	//Create channel and audio
	FMODErrorCheck(system->createChannelGroup(NULL, &channelMusic));
	FMODErrorCheck(system->createSound(songString, FMOD_SOFTWARE, 0, &audio));

	audio->getLength(&seconds, FMOD_TIMEUNIT_MS);
	audio->getDefaults(&sampleRate, 0, 0, 0);
	seconds = ((seconds + 500) / 1000);
	minutes = seconds / 60;
	seconds = seconds - (minutes * 60);

	FMODErrorCheck(system->playSound(FMOD_CHANNEL_FREE, audio, true, &songChannel1));

	hzRange = (sampleRate / 2) / static_cast<float>(sampleSize);
	songChannel1->setChannelGroup(channelMusic);
	songChannel1->setPaused(true);

	std::cout << "Song Length: " << minutes << ":" << seconds << std::endl;
	std::cout << "Sample Rate: " << sampleRate << std::endl;
	std::cout << "Freq Range: " << hzRange << std::endl;
	//songChannel1->setVolume(0);
}

BeatDetector::~BeatDetector()
{
	delete system;
}

void BeatDetector::updateTime()
{
	currentTime = GetTickCount();
	currentTime = currentTime - initialTime;
	

	if (currentMinutes > 0)
		currentSeconds = ((currentTime / 1000) - (60 * currentMinutes));
	else
		currentSeconds = (currentTime / 1000);

	if (currentSeconds != lastSeconds)
	{
		currentMillis = 0;
		lastSeconds = currentSeconds;
	}
	else
	{
		currentMillis++;
	}

	currentMinutes = ((currentTime / 1000) / 60);
}

float* BeatDetector::getCurrentSpectrum()
{
	float *specLeft, *specRight, *tempSpec;
	specLeft = new float[sampleSize];
	specRight = new float[sampleSize];
	tempSpec = new float[sampleSize / 2 + 1];

	//Get Spectrum of Song Channel for left and right
	songChannel1->getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_HAMMING);
	songChannel1->getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_HAMMING);

	//Average spectrum for stereo song channel, Divided by 2 cause Nyquist
	for (int i = 0; i < sampleSize / 2; i++)
	{
		tempSpec[i] = (specLeft[i] + specRight[i]);
		//std::cout << specStereo[i] << std::endl;
	}

	delete[] specLeft;
	delete[] specRight;

	return tempSpec;
}

float BeatDetector::calculateFluxAndSmoothing(float* currentSpectrum)
{

	specFlux = 0.0;

	//Calculate differences
	for (int i = 0; i < sampleSize / 2; i++)
	{
		difference = currentSpectrum[i] - previousFFT[i];

		if (difference > 0) {
			specFlux += difference;
		}
	}

	//Get our median for threshold
	if (spectrumFluxes.size() > 0 && spectrumFluxes.size() < 10)
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

	for (int i = 0; i < sampleSize / 2; i++)
	{
		spectrumFluxes.push_back(specFlux);

		if (spectrumFluxes.size() >= 10)
		{
			spectrumFluxes.erase(spectrumFluxes.begin());
		}
	}

	//Copy spectrum for next spectral flux calculation
	for (int j = 0; j < sampleSize / 2; j++)
		previousFFT[j] = currentSpectrum[j];

	if (smoothMedian > 1)
		thresholdSmoother = 0.8f;
	if (smoothMedian > 2 && smoothMedian < 4)
		thresholdSmoother = 1.0f;
	if (smoothMedian > 4 && smoothMedian < 6)
		thresholdSmoother = 2.2f;
	if (smoothMedian > 6)
		thresholdSmoother = 2.4f;

	return thresholdSmoother + median;
}

void BeatDetector::update()
{
		
		if (started)
		{
			float* specStereo;

			updateTime();

			specStereo = getCurrentSpectrum();

			beatThreshold = calculateFluxAndSmoothing(specStereo);

			//Beat detected
			if (specFlux > beatThreshold && (GetTickCount() - timeBetween) > 350)
			{
				smootherValues.push_back(specFlux);

				if (smootherValues.size() >= 5)
				{
					smootherValues.erase(smootherValues.begin());
				}

				timeBetween = GetTickCount();

				TimeStamp* t = new TimeStamp(currentMinutes, currentSeconds, currentMillis, specFlux);
				std::cout << "BEAT AT: " << t->getMinutes() << ":" << t->getSeconds() << ":" << t->getMilliseconds() << " -- BEAT FREQ: " << t->getFrequency() << " -- THRESHOLD: " << beatThreshold << std::endl;
				lastBeatRegistered = t;
			}
			else if ((GetTickCount() - timeBetween) > 5000)
			{
				if (thresholdSmoother>0.4f)
					thresholdSmoother -= 0.4f;

				timeBetween = GetTickCount();
			}

			songChannel1->isPlaying(&areWePlaying);

			delete[] specStereo;
		}
		else
		{
			std::cin >> test;

			if (test == 1)
				setStarted(true);
		}
		
}

FMOD::System * BeatDetector::fmodSetup()
{
	FMOD::System *system;
	FMOD_RESULT result;
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];

	// Create FMOD interface object
	result = FMOD::System_Create(&system);
	FMODErrorCheck(result);

	// Check version
	result = system->getVersion(&version);
	FMODErrorCheck(result);

	if (version < FMOD_VERSION)
	{
		std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;    return 0;
	}

	//Check Sound Cards, if none, disable sound
	result = system->getNumDrivers(&numDrivers);
	FMODErrorCheck(result);

	if (numDrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		FMODErrorCheck(result);
	}
	// At least one sound card
	else
	{
		// Get the capabilities of the default (0) sound card
		result = system->getDriverCaps(0, &caps, 0, &speakerMode);
		FMODErrorCheck(result);

		// Set the speaker mode to match that in Control Panel
		result = system->setSpeakerMode(speakerMode);
		FMODErrorCheck(result);

		// Increase buffer size if user has Acceleration slider set to off
		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			result = system->setDSPBufferSize(1024, 10);
			FMODErrorCheck(result);
		}
		// Get name of driver
		result = system->getDriverInfo(0, name, 256, 0);
		FMODErrorCheck(result);

		// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
		// PCM floating point output seems to solve it.
		if (strstr(name, "SigmaTel"))
		{
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			FMODErrorCheck(result);
		}
	}

	// Initialise FMOD
	result = system->init(100, FMOD_INIT_NORMAL, 0);

	// If the selected speaker mode isn't supported by this sound card, switch it back to stereo
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		FMODErrorCheck(result);

		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}

	FMODErrorCheck(result);

	return system;
}

void BeatDetector::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		int meh;
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		std::cin >> meh;
		exit(-1);
	}
}

void BeatDetector::setStarted(bool areWeStarted)
{
	started = areWeStarted;

	if (started)
		songChannel1->setPaused(false);
	else
		songChannel1->setPaused(true);
}

TimeStamp* BeatDetector::getLastBeat()
{
	return lastBeatRegistered;
}

bool BeatDetector::isPlaying()
{
	return areWePlaying;
}