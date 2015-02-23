#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL.h>
//#include "Level1.h"
#include "Level.h"
//#include "Level2.h"
#include "Scene.h"

class SceneManager
{
public:
	void Load();
	int getCurrent();
	void setCurrent(int);
	Scene* NextScene(SDL_Renderer*, ContentManager*);

	//Singelton
	static SceneManager* Instance()
	{
		if (instance == 0)
		{
			instance = new SceneManager();
		}
		return instance;
	}

private:
	SceneManager(){};
	static SceneManager* instance;

	//LOADING,MENU,LEVEL

	int sceneNumbers[3];

	int current;
	Scene* previous;
	Scene* active;
	int last;
};

#endif