#ifndef MENU
#define MENU

#include "Scene.h"

class Menu : public Scene
{
public:
	Menu(SDL_Renderer*, ContentManager* c);
	~Menu();
	void Update(SDL_DisplayMode );
	void Draw();
	void Event();
	bool readyToTransition();
	int getHighScore();
	bool transOut();
	bool transIn();
private:
	ContentManager * conMan;
	SDL_Renderer* rend;
	TextRenderer* t;
	TextRenderer* t2;
	SDL_Texture* textTure;
	SDL_Texture* textTure2;
	SDL_Color blue, green, red, yellow, orange, white, activeComboColor;
	SDL_Rect textRect;
	SDL_Rect textRect2;
	bool transition;
	int i;
	int transTimer;
	bool doOnce;
	bool transOutBool;
	Vector2D* transPos;
};
#endif