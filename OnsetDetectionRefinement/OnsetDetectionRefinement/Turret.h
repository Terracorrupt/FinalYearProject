#ifndef TURRET_H
#define TURRET_H

#include "Bullet.h"

class Turret : public GameObject
{
public:
	Turret(ContentManager* c, Vector2D* initial);
	~Turret();
	void Load();
	void HandleEvents();
	void Update(GameObject* g);
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit();
	void add();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	Vector2D* mousePos;
	Bullet* bullet;
	std::vector<Bullet*> bullets;
	float angle;
};
#endif