#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <SDL.h>
#include "DragMusicFile.h"
#include "Level.h"
#include "Menu.h"
#include "Scene.h"
#include "HighScoreScreen.h"

class SceneManager
{
public:
	void Load();
	int getCurrent();
	void setCurrent(int);
	Scene* NextScene(SDL_Renderer*, ContentManager*);
	Scene* getActiveScene();

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

	int sceneNumbers[5];

	int current;
	Scene* previous;
	Scene* active;
	int last;
	int highScore;
};

#endif