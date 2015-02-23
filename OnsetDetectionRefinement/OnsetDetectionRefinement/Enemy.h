#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(ContentManager* c);
	~Enemy();
	void Initialize(Vector2D*);
	void Load();
	void HandleEvents();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	int lastTick;
	bool direction;
	Vector2D* initialPos;
};
#endif