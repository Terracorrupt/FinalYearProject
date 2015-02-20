#ifndef GATE_H
#define GATE_H

#include "LargeGateObject.h"
#include <random>

class Gate
{
public:
	Gate(ContentManager* c);
	~Gate();
	void Initialize();
	void Load();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	float getX();
	//bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	LargeGateObject* gate1;
	LargeGateObject* gate2;
private:
	int rand1, rand2;
	bool alive;
};
#endif