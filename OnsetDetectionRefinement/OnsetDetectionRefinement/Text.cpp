#include "Text.h"

Text::Text(ContentManager* c, Vector2D* initial, std::string initialMessage)
{
	width = 100;
	height = 36;
	conMan = c;
	position = initial;
	message = initialMessage;
	color = {255, 255, 0};
}

Text::~Text()
{
	delete(conMan->textures["bullet"]);
}

void Text::Load()
{
	conMan->LoadTexture("../Fonts/DIMITRI.ttf", "score", width, height, 36, message, color);
	//conMan->LoadTexture("Textures/Bullet.png", "bullet", width, height, 1);
	//conMan->textures["player"]->currentFrame = 0;
	//conMan->LoadSound("Content/jump.wav", "Space");
}

void Text::Update()
{
	//Alter String text
}

void Text::Draw()
{
	conMan->DrawTexture("score", position, SDL_FLIP_NONE);
}