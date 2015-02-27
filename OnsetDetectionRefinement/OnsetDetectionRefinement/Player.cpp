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
	playerScore = 0;
	afterHit = 0;
	imHit = false;
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
	conMan->LoadTexture("../Textures/shipTemplateLCB.png", "player", width, height, 1);
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

void Player::Update(SDL_DisplayMode window)
{

	if (alive == true)
	{
		if (position->m_y < 0)
			position->m_y = 0;

		if (position->m_y > window.h - 150 - height)
			position->m_y = window.h - 150 - height;
		
		if (!imHit)
			i = SDL_GetTicks();

		if (playerScore < 0)
			playerScore = 0;

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
	if (!imHit)
		conMan->DrawTexture("player", position, SDL_FLIP_NONE);
	else
	{
		//Undraw for a bit, draw for a bit, set back imHit
		if (SDL_GetTicks() - i > 100 && SDL_GetTicks() - i < 199)
		{
			//Nothing
		}
		if (SDL_GetTicks() - i > 200 && SDL_GetTicks() - i < 399)
		{
			conMan->DrawTexture("player", position, SDL_FLIP_NONE);
		}
		if (SDL_GetTicks() - i > 400 && SDL_GetTicks() - i < 499)
		{
			
		}
		if (SDL_GetTicks() - i > 600 && SDL_GetTicks() - i < 699)
		{
			//Nothing
		}
		if (SDL_GetTicks() - i > 700 && SDL_GetTicks() - i < 799)
		{
			conMan->DrawTexture("player", position, SDL_FLIP_NONE);
		}
		if (SDL_GetTicks() - i > 900 && SDL_GetTicks() - i < 999)
		{

		}
		if (SDL_GetTicks() - i > 1000 && SDL_GetTicks() - i < 1099)
		{
			imHit = false;
		}
		
	}

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

void Player::getHit()
{
	//int i = SDL_GetTicks();
	imHit = true;
	//position->m_y += 50;

	//position->m_y -= 50;
	
}

// set the players spawn point/ so i can use checkpoints
void Player::SetSpawn(Vector2D* spawn)
{
	position = spawn;
};

