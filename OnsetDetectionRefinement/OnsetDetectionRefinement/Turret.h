#ifndef TURRET_H
#define TURRET_H

#include "Bullet.h"
#include "Player.h"

class Turret : public GameObject
{
public:
	Turret(ContentManager* c, Vector2D* initial);
	~Turret();
	void Load();
	void HandleEvents();
	void Update(Player* g);
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit();
	void add();
	void Delay();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	Vector2D* mousePos;
	Bullet* bullet;
	std::vector<Bullet*> bullets;
	float angle;
	int maxBullets;
	bool allowedShoot;
	int lastTickShot;
	bool imHit;
	int i;
};
#endif