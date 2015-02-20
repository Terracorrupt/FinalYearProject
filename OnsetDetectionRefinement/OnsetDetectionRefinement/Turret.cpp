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
}

Turret::~Turret()
{
	delete(conMan->textures["turret"]);
}

void Turret::Load()
{
	conMan->LoadTexture("Textures/Turret.png", "turret", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");
	bullet->Load();
}

void Turret::HandleEvents()
{
	mousePos = InputHandler::Instance()->GetMousePosition();
	angle = (atan2(position->m_y - mousePos->m_y, position->m_x - mousePos->m_x)*180.0000) / 3.1416;

	angle -= 180;

	if (!bullet->alive)
		bullet->position->m_y = position->m_y;

	if (InputHandler::Instance()->GetMousePressedPosition()==true)
		add();

}

void Turret::Update(GameObject* player)
{
	position->m_y = player->position->m_y + 28;

	for (std::size_t i = 0; i < bullets.size(); i++)
	{

		bullets.at(i)->Update(mousePos);


		if (bullets.at(i)->position->m_x> 1400)
			bullets.erase(bullets.begin() + i);

	}

		
	//bullets->Update(position);
}

void Turret::Draw()
{
	conMan->DrawTexture("turret", position, SDL_FLIP_NONE,angle);

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