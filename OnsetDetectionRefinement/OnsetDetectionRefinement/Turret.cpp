#include "Turret.h"

Turret::Turret(ContentManager* c, Vector2D* initial)
{
	width = 30;
	height = 22;
	conMan = c;
	gravity = true;
	alive = true;
	spaceClicked = false;
	touchingTop = false;
	touchingBottom = false;
	touchingRight = false;
	touchingLeft = false;
	onOil = false;
	position = initial;
	velocity = new Vector2D(0, 0);
	mousePos = new Vector2D(0, 0);
	bullet = new Bullet(conMan, new Vector2D(position->m_x, position->m_y));
	angle = 0;
	allowedShoot = true;
	maxBullets = 0;
	lastTickShot = 0;
}

Turret::~Turret()
{
	delete(conMan->textures["turret"]);
	delete(conMan->textures["bullet"]);
	delete bullet;
}

void Turret::Load()
{
	conMan->LoadTexture("../Textures/turret2.png", "turret", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");

	position->m_x += 35;
	bullet->Load();
}

void Turret::HandleEvents()
{
	mousePos = InputHandler::Instance()->GetMousePosition();
	angle = (atan2(position->m_y - mousePos->m_y, position->m_x - mousePos->m_x)*180.0000) / 3.1416;

	angle -= 180;

	if (!bullet->alive)
		bullet->position->m_y = position->m_y;

	if (InputHandler::Instance()->GetMousePressedPosition() == true && allowedShoot)
	{
		add();
		maxBullets++;
		lastTickShot = SDL_GetTicks();

		Delay();
	}

	if (maxBullets > 1)
	{
		allowedShoot = false;
		if (SDL_GetTicks() - lastTickShot > 500)
		{
			allowedShoot = true;
			maxBullets = 0;
		}
	}
	else if (!allowedShoot)
	{
		if (SDL_GetTicks() - lastTickShot > 20)
		{
			allowedShoot = true;
		}
	}

}

void Turret::Update(Player* player)
{
	position->m_y = player->position->m_y + 28;

	for (std::size_t i = 0; i < bullets.size(); i++)
	{

		bullets.at(i)->Update(mousePos);

		if (bullets.at(i)->position->m_x> 1400 || bullets.at(i)->position->m_x < 0)
			bullets.erase(bullets.begin() + i);
		else if (bullets.at(i)->position->m_y> 900 || bullets.at(i)->position->m_x < -20)
			bullets.erase(bullets.begin() + i);

		//if (!bullets.at(i)->alive)
		//{
			//bullets.erase(bullets.begin() + i);
		//}

	}

	if (player->imHit)
	{
		imHit = true;
	}
	else
	{
		imHit = false;
		i = SDL_GetTicks();
	}
		

	//bullets->Update(position);
}

void Turret::Draw()
{
	if (!imHit)
		conMan->DrawTexture("turret", position, SDL_FLIP_NONE,angle);
	else
	{
		//Undraw for a bit, draw for a bit, set back imHit
		if (SDL_GetTicks() - i > 100 && SDL_GetTicks() - i < 199)
		{
			//Nothing
		}
		if (SDL_GetTicks() - i > 200 && SDL_GetTicks() - i < 399)
		{
			conMan->DrawTexture("turret", position, SDL_FLIP_NONE);
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
			conMan->DrawTexture("turret", position, SDL_FLIP_NONE);
		}
		if (SDL_GetTicks() - i > 900 && SDL_GetTicks() - i < 999)
		{

		}
		if (SDL_GetTicks() - i > 1000 && SDL_GetTicks() - i < 1099)
		{
			imHit = false;
		}
	}

	for (std::size_t i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->Draw();
	}
}

void Turret::getHit()
{

}

void Turret::add()
{
	Bullet* b = new Bullet(conMan, new Vector2D(position->m_x + 20, position->m_y + 2));
	b->alive = true;
	bullets.push_back(b);
}

void Turret::Delay()
{
	allowedShoot = false;
}