#include "Menu.h"

Menu::Menu(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;

	player = new Player(conMan);
	player->Load();

	gateManager = new GateManager(r,conMan);
	//gateManager->Initialize();
	//gate->Load();

	DEBUG_MSG("Menu Created");
}

Menu::~Menu()
{
	delete player;
	delete gateManager;
}
void Menu::Update()
{
	//conMan->Update();
	player->Update();
	gateManager->Update(player);
}

void Menu::Draw()
{
	player->Draw();
	gateManager->Draw();
}

void Menu::Event()
{
	player->HandleEvents();
}