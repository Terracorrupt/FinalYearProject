#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(ContentManager* c);
	~Player();
	void Initialize();
	void Load();
	void HandleEvents();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
};
#endif