#include "Bullet.h"

Bullet::Bullet(ContentManager* c, Vector2D* initial)
{
	width = 10;
	height = 10;
	conMan = c;
	speed = 10.0f;
	gravity = true;
	alive = false;
	spaceClicked = false;
	touchingTop = false;
	touchingBottom = false;
	touchingRight = false;
	touchingLeft = false;
	onOil = false;
	position = initial;
	velocity = new Vector2D(0, 0);
	angle = new Vector2D(0, 0);
	shot = false;
}

Bullet::~Bullet()
{
	delete(conMan->textures["bullet"]);
}

void Bullet::Load()
{
	conMan->LoadTexture("Textures/Bullet.png", "bullet", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");
}

void Bullet::Update(Vector2D* towards)
{
	if (!shot)
	{
		float a = atan2(position->m_y - towards->m_y, position->m_x - towards->m_x);

		angle->m_x = std::cos(a);
		angle->m_y = std::sin(a);
		
		shot = true;
	}

	if (alive)
	{
		position->m_x -= angle->m_x * speed;
		position->m_y -= angle->m_y * speed;
	}
}

void Bullet::Draw()
{
	if (alive)
		conMan->DrawTexture("bullet", position, SDL_FLIP_NONE);
}