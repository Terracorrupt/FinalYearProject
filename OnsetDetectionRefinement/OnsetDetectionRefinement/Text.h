#ifndef TEXT_H
#define TEXT_H

#include "GameObject.h"

class Text : public GameObject
{
public:
	Text(ContentManager* c, Vector2D* v, std::string initialMsg);
	~Text();
	void Initialize();
	void Load();
	void Update();
	void Draw();
	void SetSpawn(Vector2D* spawn);
	void getHit();
	bool touchingLeft, touchingRight, touchingTop, touchingBottom, spaceClicked, gravity, onOil;
	Vector2D* velocity;
	std::string message;
	SDL_Color color;
};

#endif