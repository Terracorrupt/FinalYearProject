#include "Menu.h"

Menu::Menu(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;
	rend = r;

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);
	white = { 255, 255, 255 };

	t->message = "MENU";
	textTure = t->RenderText(t->message, white);
	textRect.x = 500;
	textRect.y = 300;
	textRect.w = 100;
	textRect.h = 50;

	SDL_RenderCopy(r, textTure, 0, &textRect);

	DEBUG_MSG("Menu Created");

	transition = false;
	i = SDL_GetTicks();
}

Menu::~Menu()
{
	delete t;
	delete conMan;
	delete rend;
}

void Menu::Event()
{
	
}

void Menu::Update(SDL_DisplayMode window)
{
	textRect.x = window.w / 2 - 100;
	textRect.y = window.h / 2 - 100;

	if (SDL_GetTicks() - i > 300)
	{
		transition = true;
	}
}

void Menu::Draw()
{
	SDL_RenderCopy(rend, textTure, 0, &textRect);
}

bool Menu::readyToTransition()
{
	return transition;
}

int Menu::getHighScore()
{
	return 0;
}