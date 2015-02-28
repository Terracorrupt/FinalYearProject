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
	doOnce = false;
	transOutBool = false;
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

	if (!doOnce)
	{
		conMan->LoadTexture("../Textures/transitionOut.png", "transOut", window.w*1.5, window.h, 1);
		transPos = new Vector2D(-(window.w*1.5), 0);
		doOnce = true;
	}

	if (SDL_GetTicks() - i > 300 && !transition)
	{
		transition = true;
	}
}

void Menu::Draw()
{
	SDL_RenderCopy(rend, textTure, 0, &textRect);

	if (transition)
		conMan->DrawTexture("transOut", transPos, SDL_FLIP_NONE);
}

bool Menu::readyToTransition()
{
	return transition;
}

int Menu::getHighScore()
{
	return 0;
}

bool Menu::transOut()
{

	if (!transOutBool)
		transTimer = SDL_GetTicks();

	transOutBool = true;

	//int i = SDL_GetTicks();

	if (SDL_GetTicks() - transTimer < 1000)
	{
		transPos->m_x += 40;
		conMan->DrawTexture("transOut", transPos, SDL_FLIP_NONE);
		return false;
	}
		
	return true;
}

bool Menu::transIn()
{
	return true;
}