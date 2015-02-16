#ifndef SCENE
#define SCENE

#include <SDL.h>
#include "SDL_image.h"
#include "Debug.h"
#include "ContentManager.h"
//#include "InputManager.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "SDL_mixer.h"
#include <math.h>
#include <iostream>
//#include "Obstacle.h"

class Scene
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	//Mix_Music* music;
};
#endif