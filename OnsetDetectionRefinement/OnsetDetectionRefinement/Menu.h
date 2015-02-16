#ifndef MENU
#define MENU

#include "Scene.h"

class Menu : public Scene
{
public:
	Menu(SDL_Renderer*);
	~Menu();
	void Update();
	void Draw();
private:
	//Generic* m;
};
#endif