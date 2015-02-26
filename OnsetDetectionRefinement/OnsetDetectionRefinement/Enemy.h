#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(ContentManager* c, SDL_Renderer* r);
	~Enemy();
	void Initialize(Vector2D*);
	void Load();
	void HandleEvents();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit(int amount);
	bool isDead();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	int lastTick;
	bool direction;
	Vector2D* initialPos;
	TextRenderer* t;
	SDL_Color blue, green, red, yellow, orange, white, activeColor;
	bool areWeDead;
	int deadMillis;
	SDL_Rect textRect;
	float hover;
	int amount;
	SDL_Texture * textTure;
};
#endif