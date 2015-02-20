#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include "Debug.h"

#include <iostream>

class Collision
{
public:
	static Collision* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Collision();
		}

		return s_pInstance;
	}

	bool CheckCollision(SDL_Rect, SDL_Rect);
private:
	Collision();
	~Collision();
	static Collision* s_pInstance;
};
#endif
typedef Collision TheCollision;