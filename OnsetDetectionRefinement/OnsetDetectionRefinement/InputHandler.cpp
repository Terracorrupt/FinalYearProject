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

// returns the current position of the mouse
Vector2D* InputHandler::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePosition = new Vector2D((float)x, (float)y);
	return mousePosition;
};