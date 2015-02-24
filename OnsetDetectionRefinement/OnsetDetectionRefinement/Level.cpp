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

	t->message = "00000";
	SDL_Texture* textTure = t->RenderText(t->message, white);
	textRect.x = 40;
	textRect.y = 15;
	textRect.w = 100;
	textRect.h = 50;

	t2->message = "x0";
	SDL_Texture*  textTure2 = t->RenderText(t->message, activeComboColor);
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
	prevCombo = 0;
	prevEnemyScore = 0;
	prevGateScore = 0;

	DEBUG_MSG("Level Created");

	SDL_DestroyTexture(textTure);
	SDL_DestroyTexture(textTure2);
	skyTrue = false;
	//conMan->LoadTexture("../Textures/sky.png", "sky", 1200, 768, 1);

	BeatDetector::Instance()->setStarted(true);
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
	delete conMan->textures["sky"];
}
void Level::Update(SDL_DisplayMode window)
{

	//COMBO STUFF STARTS IN
	prevScore = finalScore;
	prevEnemyScore = enemyManager->getEnemyScore();
	prevGateScore = player->playerScore;
	
	BeatDetector::Instance()->update();

	//conMan->Update();
	player->Update(window);
	turret->Update(player);
	gateManager->Update(player, window);
	enemyManager->Update(player, turret);

	if (combo<36)
		combo = enemyManager->getCombo() + gateManager->getCombo();
	if (combo >= 36)
		combo = 35;
	if (combo<0)
		combo = 1;

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
		
	if (prevCombo > 1 && finalCombo == 1)
	{
		finalScore = prevScore - 100;
		player->playerScore = prevGateScore*prevCombo;
		enemyManager->setCombo(prevEnemyScore*prevCombo);
		finalScore = ((player->playerScore + enemyManager->getEnemyScore())*prevCombo -100);
		enemyManager->enemyCombo = 1;
		gateManager->gateCombo = 1;
	}
	else if (finalCombo > 1)
		finalScore = ((player->playerScore + enemyManager->getEnemyScore())*finalCombo);
	else
		finalScore = ((player->playerScore + enemyManager->getEnemyScore()));

	

	std::string s = std::to_string(finalScore);

	if (finalScore == 0)
		s.insert(0, "00000");
	else if (finalScore < 1000)
		s.insert(0, "000");
	else if (finalScore >= 1000 && finalScore < 10000)
		s.insert(0, "00");
	

	std::string s2 = std::to_string(finalCombo);
	s2.insert(0, "x");

	t->message = s;
	t2->message = s2;

	prevCombo = finalCombo;


	//RESIZING
	if (window.w > 1200)
	{
		textRect.w = 160;
		textRect.h = 70;
		textRect.x = 50;
		textRect.y = 20;

		if (!skyTrue)
		{
			conMan->LoadTexture("../Textures/sky.png", "sky", window.w, window.h, 1);
			skyTrue = true;
		}

	}
		
		
	
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
		SDL_DestroyTexture(textTure);
		SDL_DestroyTexture(textTure2);
		
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