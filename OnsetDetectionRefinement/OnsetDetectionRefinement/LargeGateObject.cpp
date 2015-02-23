#include "LargeGateObject.h"

LargeGateObject::LargeGateObject(ContentManager* c)
{
	width = 40;
	height = 466;
	conMan = c;
	//gravity = true;
	alive = true;
	//spaceClicked = false;
	touchingTop = false;
	touchingBottom = false;
	touchingRight = false;
	touchingLeft = false;
	//onOil = false;
	position = new Vector2D(700, 300);
	velocity = new Vector2D(0, 0);
}

LargeGateObject::~LargeGateObject()
{
	delete(conMan->textures["gate"]);
}

void LargeGateObject::Initialize(float s)
{
	position = new Vector2D(700, 300);
	speed = s;
	
}

void LargeGateObject::Load()
{
	conMan->LoadTexture("../Textures/gate2.png", "gate", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");
}

void LargeGateObject::Update()
{

	//if (alive == true)
	
	position->m_x -= speed;
	

}

void LargeGateObject::Draw()
{

	conMan->DrawTexture("gate", position, SDL_FLIP_NONE);

	/*if (alive == true)
	{
	if (gravity == true)
	{
	conMan->DrawTexture("player", position, SDL_FLIP_NONE);
	}

	if (gravity == false)
	{
	conMan->DrawTexture("player", position, SDL_FLIP_VERTICAL);
	}
	}*/
}

// set the players spawn point/ so i can use checkpoints
void LargeGateObject::SetSpawn(Vector2D* spawn)
{
	position = spawn;
};
