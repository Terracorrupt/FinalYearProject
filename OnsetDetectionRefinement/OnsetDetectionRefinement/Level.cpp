#include "Level.h"

Level::Level(SDL_Renderer* r, ContentManager* c)
{
	conMan = c;

	player = new Player(conMan);
	player->Load();

	rend = r;
	 

	i++;
	DEBUG_MSG(i);

	turret = new Turret(conMan, new Vector2D(player->position->m_x +25, player->position->m_y - 40));
	turret->Load();

	gateManager = new GateManager(r,conMan);
	enemyManager = new EnemyManager(r, conMan);

	//gateManager->Initialize();
	//gate->Load();

	t = new TextRenderer(r, "../Fonts/DIMITRI.ttf",28);
	t2 = new TextRenderer(r, "../Fonts/DIMITRI.ttf", 28);

	//t->Load();
	white = { 255, 255, 255 };
	blue = { 0, 0, 255 };
	red = { 255, 0, 0 };
	green = { 0, 255, 0 };
	yellow = { 255, 255, 0 };
	orange = { 255, 50, 0 };
	activeComboColor = blue;

	t->message = "0000";
	textTure = t->RenderText(t->message, white);
	textRect.x = 40;
	textRect.y = 15;
	textRect.w = 80;
	textRect.h = 50;

	t2->message = "x0";
	textTure2 = t->RenderText(t->message, activeComboColor);
	textRect2.x = 600;
	textRect2.y = 15;
	textRect2.w = 80;
	textRect2.h = 50;

	SDL_RenderCopy(r, textTure, 0, &textRect);
	SDL_RenderCopy(r, textTure2, 0, &textRect2);

	finalScore = 0;
	prevScore = 0;
	combo = 0;
	finalCombo = 0;
	
	DEBUG_MSG("Menu Created");

	conMan->LoadTexture("../Textures/sky.png", "sky", 1200, 768, 1);
}

Level::~Level()
{
	delete player;
	delete gateManager;
	delete enemyManager;
	delete turret;
	delete t;
	delete t2;
	delete conMan;
	delete textTure;
	delete textTure2;
	delete conMan->textures["sky"];
}
void Level::Update()
{
	prevScore = finalScore;

	//conMan->Update();
	player->Update();
	turret->Update(player);
	gateManager->Update(player);
	enemyManager->Update(player, turret);

	if (combo<36)
		combo = enemyManager->getCombo() + gateManager->getCombo();
	if (combo >= 36)
		combo = 35;


	if (finalCombo < 6)
	{
		finalCombo = combo / 7;

		if (finalCombo == 0)
			finalCombo = 1;
	}

	if (finalCombo == 1)
	{
		activeComboColor = blue;
	}
	else if (finalCombo == 2)
	{
		activeComboColor = green;
	}
	else if (finalCombo == 2)
	{
		activeComboColor = yellow;
	}
	else if (finalCombo == 3)
	{
		activeComboColor = orange;
	}
	else
	{
		activeComboColor = red;
	}
		

	if (finalCombo>0)
		finalScore = ((player->playerScore + enemyManager->getEnemyScore())*finalCombo);
	else
		finalScore = player->playerScore + enemyManager->getEnemyScore();

	std::string s = std::to_string(finalScore);

	if (finalScore == 0)
		s.insert(0, "0000");
	else if (finalScore < 1000)
		s.insert(0, "00");
	else if (finalScore >= 1000 && finalScore < 10000)
		s.insert(0, "0");
	

	std::string s2 = std::to_string(finalCombo);
	s2.insert(0, "x");

	t->message = s;
	t2->message = s2;

	
	//t->setMessage(s);
	//t->Update();
}

void Level::Draw()
{
	conMan->DrawTexture("sky", new Vector2D(0, 0), SDL_FLIP_NONE);
	player->Draw();
	turret->Draw();
	enemyManager->Draw();
	gateManager->Draw();
	//t->Draw();

	if (finalScore != prevScore)
	{
		textTure = t->RenderText(t->message, white);
		textTure2 = t->RenderText(t2->message, activeComboColor);

	}
	
	SDL_RenderCopy(rend, textTure, 0, &textRect);
	SDL_RenderCopy(rend, textTure2, 0, &textRect2);

	//textRect.x = 40;
	//textRect.y = 15;
	//textRect.w = 80;
	//textRect.h = 50;

	
	//textRect2.x = 600;
	//textRect2.y = 15;
	//textRect2.w = 80;
	//textRect2.h = 50;

	
	
}

void Level::Event()
{
	player->HandleEvents();
	turret->HandleEvents();
}