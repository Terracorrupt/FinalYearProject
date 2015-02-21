#ifndef LARGEGATEOBJECT_H
#define LARGEGATEOBJECT_H

#include "GameObject.h"

class LargeGateObject : public GameObject
{
public:
	LargeGateObject(ContentManager* c);
	~LargeGateObject();
	void Initialize(float);
	void Load();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	float speed;
};
#endif