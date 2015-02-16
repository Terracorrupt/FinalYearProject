#include "BeatDetector.h"

int main()
{
	BeatDetector* detector = new BeatDetector(1024, "Sound/gangam.mp3"); 
	int test;

	detector->setStarted(false);

	while (detector->isPlaying())
		detector->update();

	std::cin >> test;

	return 0;
}
