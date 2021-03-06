#include "SceneManager.h"

SceneManager* SceneManager::instance=0; 

void SceneManager::Load()
{
	sceneNumbers[0] = 1;
	sceneNumbers[1] = 2;
	sceneNumbers[2] = 3;
	sceneNumbers[3] = 4;
	sceneNumbers[4] = 5;

	//CURRENT SCENE
	current = 2;
	last = 1;
	highScore = 0;
}

int SceneManager::getCurrent()
{
	return current;
}

void SceneManager::setCurrent(int i)
{
	current = i;
}

Scene* SceneManager::getActiveScene()
{
	return active;
}

Scene* SceneManager::NextScene(SDL_Renderer* r, ContentManager* c)
{
	switch (current)
	{
	case 1: //Loading
		break;
	case 2: //Menu
		if (last != 2)
		{
			active = new Menu(r, c);
			last = 2;
			previous = active;
		}
		break;
	case 3: //DragFile
		if (last != 3)
		{
			active = new DragMusicFile(r, c);
			last = 3;
			previous = active;
		}
		break;
	case 4: //Level
		if (last != 4)
		{
			active = new Level(r, c);
			last = 4;
			previous = active;
		}
		break;
	case 5: //HighScoreScreen
		if (last != 5)
		{
			if (last == 4)
			{
				highScore = active->getHighScore();
			}

			active = new HighScoreScreen(r, c,highScore);
			last = 5;
			previous = active;
		}
		break;
	}
	return active;
}
