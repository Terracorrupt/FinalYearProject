#include "BeatDetector.h"
#include <SDL.h>
#include "Game.h"
#undef main

int main()
{
	//BeatDetector* detector = new BeatDetector(1024, "Sound/SK1.mp3"); 
	int test;

	//BeatDetector::Instance()->Load(1024, "../Sound/dino.mp3");

	

	


	float FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;
	Uint32 frameStart, frameTime;

	DEBUG_MSG("Game Object Created");

	TheGame::Instance()->Initialize("Onset Detector", 50,50, 1200, 768, 0);
	DEBUG_MSG("Game Initialised");

	DEBUG_MSG("Game Loop Starting......");
	while (TheGame::Instance()->IsRunning())
	{
		frameStart = SDL_GetTicks();
		TheGame::Instance()->HandleEvents();
		TheGame::Instance()->Update();
		TheGame::Instance()->Render();

		//BeatDetector::Instance()->update();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	DEBUG_MSG("Calling Cleanup");
	TheGame::Instance()->CleanUp();

	BeatDetector::Instance()->setStarted(false);

	//while (detector->isPlaying())
		//detector->update();

	std::cin >> test;

	return 0;
}
