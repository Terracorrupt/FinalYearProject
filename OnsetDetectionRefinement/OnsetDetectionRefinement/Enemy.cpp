#include "Enemy.h"

Enemy::Enemy(ContentManager* c, SDL_Renderer* r)
{
	width = 40;
	height = 46;
	conMan = c;
	renderer = r;
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

	white = { 255, 255, 255 };
	blue = { 0, 100, 255 };
	red = { 255, 0, 0 };
	green = { 0, 255, 0 };
	yellow = { 255, 255, 0 };
	orange = { 255, 165, 0 };

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);

	areWeDead = false;
	hover = 0;
	amount = 0;
	
	if (rand() % 20 >= 16)
		isSpecial = true;
	else
		isSpecial = false;
	speed = 3.0f;
}

Enemy::~Enemy()
{
	delete velocity;
	delete position;
	delete renderer;
	delete conMan;
	delete initialPos;
	delete t;
	SDL_DestroyTexture(textTure);
	delete textTure;

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

void Enemy::Update(GameObject* player)
{
	if (alive == true)
	{
		if (!isSpecial)
		{
			if (!direction)
			{
				position->m_x -= 3;
				position->m_y -= 2;
			}
		else
		{
			position->m_x -= 3;
			position->m_y += 2;
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
		//SPECIAL
		else
		{
			if (speed< 25)

			if (position->m_x > player->position->m_x && position->m_y < player->position->m_y -10)
			{
				position->m_x -= speed;
				position->m_y += speed;
			}
			else if (position->m_x > player->position->m_x && position->m_y > player->position->m_y + 10)
			{
				position->m_x -= speed;
				position->m_y -= speed;
			}
			else if (position->m_x > player->position->m_x)
			{
				position->m_x -= speed;
			}

			else if (position->m_y < player->position->m_y)
			{
				position->m_y += speed;
			}

			else if (position->m_y > player->position->m_y)
			{
				position->m_y -= speed;
			}
			speed += 0.05f * 2;
		}

		
		deadMillis = SDL_GetTicks();
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
		
		textRect.x = position->m_x;
		textRect.y = position->m_y - hover;
		textRect.w = 75;
		textRect.h = 45;

		SDL_RenderCopy(renderer, textTure, 0, &textRect);

		hover += 5;

		if (SDL_GetTicks() - deadMillis > 400)
		{
			areWeDead = true;
		}
	}
	
}

// set the players spawn point / so i can use checkpoints
void Enemy::SetSpawn(Vector2D* spawn)
{
	position = spawn;
}

void Enemy::getHit(int a)
{
	if (a == 50)
	{
		t->message = "+50";
		activeColor = blue;

	}
	else if (a == 100)
	{
		t->message = "+100";
		activeColor = green;
	}
	else if (a == 150)
	{
		t->message = "+150";
		activeColor = yellow;
	}
	else if (a == 200)
	{
		t->message = "+200";
		activeColor = orange;
	}
	else if (a == 250)
	{
		t->message = "+250";
		activeColor = red;
	}

	textTure = t->RenderText(t->message, activeColor);
	amount = a;
}

bool Enemy::isDead()
{
	return areWeDead;
}