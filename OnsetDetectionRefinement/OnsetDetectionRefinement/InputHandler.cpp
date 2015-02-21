#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
	keyState = SDL_GetKeyboardState(0);
}

InputHandler::~InputHandler()
{
}

// check to see if a key is pressed
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (keyState != 0)
	{
		if (keyState[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	

	return false;
}

bool InputHandler::GetMousePressedPosition()
{
	int x, y;

	x = 0;
	y = 0;

	if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
	{
		SDL_GetMouseState(&x, &y);
		mousePosition = new Vector2D((float)x, (float)y);
		
		//DEBUG_MSG("YOOO");

		return true;
	}

	return false;

}

bool InputHandler::event(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		mx = e.motion.x;
		my = e.motion.y;
	}

	return true;
}

Vector2D* InputHandler::motionVector()
{
	Vector2D * newVec = new Vector2D(mx, my);
	return newVec;
}

// returns the current position of the mouse
Vector2D* InputHandler::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePosition = new Vector2D((float)x, (float)y);

	return mousePosition;

};