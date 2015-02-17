// Allow me to call a simple function to check if a key is pressed
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <iostream>
#include "Vector2D.h"

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	virtual Vector2D* GetMousePosition();
	virtual bool isKeyDown(SDL_Scancode);
	Vector2D* mousePosition;
	const Uint8* keyState;

private:
	InputHandler();
	~InputHandler();
	static InputHandler* s_pInstance;
};
#endif
typedef InputHandler TheInputHandler;