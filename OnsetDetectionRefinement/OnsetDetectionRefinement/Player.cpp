#include "Player.h"

Player::Player(ContentManager* c)
{
	width = 66;
	height = 60;
	conMan = c;
	gravity = true;
	alive = true;
	spaceClicked = false;
	touchingTop = false;
	touchingBottom = false;
	touchingRight = false;
	touchingLeft = false;
	onOil = false;
	position = new Vector2D(100, 300);
	velocity = new Vector2D(0, 0);
}

Player::~Player()
{
	delete(conMan->textures["player"]);
}

void Player::Initialize()
{
	position = new Vector2D(0, 0);
}

void Player::Load()
{
	conMan->LoadTexture("Textures/test.png", "player", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");
}

void Player::HandleEvents()
{
	if (alive == true)
	{
		
			if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
			{
				if (velocity->m_y > -7)
					velocity->m_y -= 0.4;
				else
					velocity->m_y += 0.2;

				position->m_y += velocity->m_y;


				//position->m_y -= 7;
				conMan->textures["player"]->currentFrame = 0;
			}
			else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
			{
				if (velocity->m_y<10)
					velocity->m_y += 0.4;
				else
					velocity->m_y -= 0.2;

				//position->m_y += 7;
				conMan->textures["player"]->currentFrame = 0;
			}
			else
			{
				/*if (velocity->m_y > 0)
				{
					velocity->m_y -= 0.1f;
				}
				if (velocity->m_y < 0)
				{
					velocity->m_y += 0.1f;
				}*/
				velocity->m_y = 0;
			}

			position->m_y += velocity->m_y;
			
	}
}

void Player::Update()
{

	conMan->Update();
	/*if (alive == true)
	{
		if (gravity == false)
		{
			if (touchingTop == false)
			{
				position->m_y -= 2;
			}
		}

		if (gravity == true)
		{
			if (touchingBottom == false)
			{
				position->m_y += 2;
			}
		}
	}

	if (alive == false)
	{
		position = spawnPoint;
		alive = true;
		gravity = true;
		conMan->textures["player"]->currentFrame = 0;
	}*/
}

void Player::Draw()
{

	conMan->DrawTexture("player", position, SDL_FLIP_NONE);

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
void Player::SetSpawn(Vector2D* spawn)
{
	position = spawn;
};