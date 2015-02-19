#ifndef MENU
#define MENU

#include "Scene.h"

class Menu : public Scene
{
public:
	Menu(SDL_Renderer*, ContentManager* c);
	~Menu();
	void Update();
	void Draw();
	void Event();
private:
	GateManager* gateManager;
	Player* player;
	ContentManager * conMan;
};
#endif