#ifndef LEVEL
#define LEVEL

#include "Scene.h"

class Level : public Scene
{
public:
	Level(SDL_Renderer*, ContentManager* c);
	~Level();
	void Update();
	void Draw();
	void Event();
private:
	GateManager* gateManager;
	EnemyManager* enemyManager;
	Player* player;
	Turret* turret;
	ContentManager * conMan;
	SDL_Renderer* rend;
	TextRenderer* t;
	TextRenderer* t2;
	int finalScore;
	int prevScore;
	int i = 0;
	int combo;
	int finalCombo;
	SDL_Texture* textTure;
	SDL_Texture* textTure2;
	SDL_Color blue, green, red, yellow, orange, white, activeComboColor;
	SDL_Rect textRect;
	SDL_Rect textRect2;
};
#endif