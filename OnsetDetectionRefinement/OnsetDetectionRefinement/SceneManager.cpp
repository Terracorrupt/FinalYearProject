#include "SceneManager.h"

SceneManager* SceneManager::instance=0; 

void SceneManager::Load()
{
	sceneNumbers[0] = 1;
	sceneNumbers[1] = 2;
	sceneNumbers[2] = 3;

	//CURRENT SCENE
	current = 2;
	last = 1;
}

int SceneManager::getCurrent()
{
	return current;
}

void SceneManager::setCurrent(int i)
{
	current = i;
}

Scene* SceneManager::NextScene(SDL_Renderer* r, ContentManager* c)
{
	switch (current)
	{
	case 1: //Loading
		break;
	case 2: //Level
		if (last != 2)
		{
			active = new Level(r, c);
			last = 2;
			previous = active;
		}
		break;
	case 3: //Menu
		if (last != 3)
		{
			//active = new Level(r);
			last = 3;
			previous = active;
		}
		break;
	}
	return active;
}
