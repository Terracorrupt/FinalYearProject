// Abstract class to provide common attributes to game objects
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Debug.h"
#include "Texture.h"
#include "InputHandler.h"
#include "ContentManager.h"
#include "TextRenderer.h"


using namespace std;

class GameObject
{
public:
	virtual void Load() = 0;
	Vector2D* position;
	SDL_Renderer* renderer;
	ContentManager* conMan;
	float speed;
	bool alive;
	int height;
	int width;
	int type;
	bool collidable;
};
#endif