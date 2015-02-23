#include "Enemy.h"

Enemy::Enemy(ContentManager* c)
{
	width = 40;
	height = 46;
	conMan = c;
	gravity = true;
	alive = true;
	spaceClicked = false;
	touchingTop = false;
	touchingBottom = false;
	touchingRight = false;
	touchingLeft = false;
	onOil = false;
	position = new Vector2D(0, 0);
	velocity = new Vector2D(0, 0);
	lastTick = SDL_GetTicks();
	direction = false;
}

Enemy::~Enemy()
{
	delete velocity;
	delete position;
	
}

void Enemy::Initialize(Vector2D* initial)
{
	position = initial;
	initialPos=initial;
}

void Enemy::Load()
{
	conMan->LoadTexture("../Textures/enemyTest.png", "enemy", width, height, 1);
}

void Enemy::Update()
{
	if (alive == true)
	{
		if (!direction)
		{
			position->m_x -= 3;
			position->m_y -= 4;
		}
		else
		{
			position->m_x -= 3;
			position->m_y += 4;
		}

		if (SDL_GetTicks() - lastTick > 700)
		{
			if (direction)
				direction = false;
			else
				direction = true;
			lastTick = SDL_GetTicks();
		}
	}
	else
	{
		
	}
}

void Enemy::Draw()
{
	if (alive == true)
	{
		conMan->DrawTexture("enemy", position, SDL_FLIP_NONE);
	}
	else
	{
		
	}
	
}

// set the players spawn point / so i can use checkpoints
void Enemy::SetSpawn(Vector2D* spawn)
{
	position = spawn;
}