#include "Menu.h"

Menu::Menu(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;

	player = new Player(conMan);
	player->Load();

	DEBUG_MSG("Menu Created");
}

Menu::~Menu()
{
	delete player;
}
void Menu::Update()
{
	//conMan->Update();
	player->Update();
}

void Menu::Draw()
{
	player->Draw();
}

void Menu::Event()
{
	player->HandleEvents();
}