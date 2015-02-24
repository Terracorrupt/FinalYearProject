#ifndef LARGEGATEOBJECT_H
#define LARGEGATEOBJECT_H

#include "GameObject.h"

class LargeGateObject : public GameObject
{
public:
	LargeGateObject(ContentManager* c, bool top);
	~LargeGateObject();
	void Initialize(float);
	void Load();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* initial;
	float speed;
	bool topOrBottom;
};
#endif