#include "Player.h"

Player::Player(ContentManager* c)
{
	width = 70;
	height = 76;
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
	conMan->LoadTexture("Textures/Ship.png", "player", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");
}

void Player::HandleEvents()
{
	if (alive == true)
	{
		
			if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
			{
			
				velocity->m_y = -6;
			
				position->m_y += velocity->m_y;


				//position->m_y -= 7;
				conMan->textures["player"]->currentFrame = 0;
			}
			else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
			{
				
				velocity->m_y = 12;
			

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

			/*if (position->m_y < 0)
				position->m_y = 0;

			if (position->m_y > 768 - height)
				position->m_y = 768 - height;*/
			
	}
}

void Player::Update()
{

	if (alive == true)
	{
		if (position->m_y < 0)
			position->m_y = 0;

		if (position->m_y > 768 - height)
			position->m_y = 768 - height;

	}

	if (alive == false)
	{
		//position = spawnPoint;
		//alive = true;
		//gravity = true;
		//conMan->textures["player"]->currentFrame = 0;
	}
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