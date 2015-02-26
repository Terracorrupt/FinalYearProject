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
//#include "SceneManager.h"
//#include "SDL_mixer.h"
#include <math.h>
#include <iostream>
#include "Turret.h"
#include "Bullet.h"
#include "TrackVisualizer.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "FMODErrorCheck.h"


class Scene
{
public:
	virtual void Update(SDL_DisplayMode) = 0;
	virtual void Draw() = 0;
	virtual void Event() = 0;
	virtual bool readyToTransition() = 0;
	virtual int getHighScore() = 0;
	//Mix_Music* music;
};
#endif