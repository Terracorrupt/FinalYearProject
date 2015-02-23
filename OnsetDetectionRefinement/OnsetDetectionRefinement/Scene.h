#ifndef SCENE
#define SCENE

#include <SDL.h>
#include "SDL_image.h"
#include "Debug.h"
#include "ContentManager.h"
#include "InputHandler.h"
#include "Player.h"
#include "GateManager.h"
#include "EnemyManager.h"
//#include "SDL_mixer.h"
#include <math.h>
#include <iostream>
#include "Turret.h"
#include "Bullet.h"
#include "TextRenderer.h"


class Scene
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Event() = 0;
	//Mix_Music* music;
};
#endif