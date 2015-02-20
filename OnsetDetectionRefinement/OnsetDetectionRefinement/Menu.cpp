#include "Menu.h"

Menu::Menu(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;

	player = new Player(conMan);
	player->Load();

	i++;
	DEBUG_MSG(i);

	turret = new Turret(conMan, new Vector2D(player->position->m_x +25, player->position->m_y - 40));
	turret->Load();

	gateManager = new GateManager(r,conMan);

	//gateManager->Initialize();
	//gate->Load();

	t = new Text(c, new Vector2D(100, 100), "Score: 0000");
	t->Load();
	
	DEBUG_MSG("Menu Created");
}

Menu::~Menu()
{
	delete player;
	delete gateManager;
	delete turret;
	delete t;
}
void Menu::Update()
{
	//conMan->Update();
	player->Update();
	turret->Update(player);
	gateManager->Update(player);
	t->Update();
}

void Menu::Draw()
{
	player->Draw();
	turret->Draw();
	gateManager->Draw();
	t->Draw();
}

void Menu::Event()
{
	player->HandleEvents();
	turret->HandleEvents();
}