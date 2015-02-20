#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(ContentManager* c, Vector2D* initial);
	~Bullet();
	void Load();
	void HandleEvents();
	void Update(Vector2D* towards);
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	Vector2D* angle;
	bool shot;
};
#endif