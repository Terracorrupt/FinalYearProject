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
	blue = { 0, 100, 255 };
	red = { 255, 0, 0 };
	green = { 0, 255, 0 };
	yellow = { 255, 255, 0 };
	orange = { 255, 165, 0 };
	pink = {255,20,147};
	activeComboColor = blue;

	t->message = "00000";
	SDL_Texture* textTure = t->RenderText(t->message, white);
	textRect.x = 40;
	textRect.y = 15;
	textRect.w = 100;
	textRect.h = 50;

	t2->message = "x0";
	SDL_Texture*  textTure2 = t->RenderText(t->message, activeComboColor);
	textRect2.x = 40;
	textRect2.y = 500;
	textRect2.w = 80;
	textRect2.h = 50;

	SDL_RenderCopy(r, textTure, 0, &textRect);
	SDL_RenderCopy(r, textTure2, 0, &textRect2);

	finalScore = 0;
	prevScore = 0;
	combo = 0;
	finalCombo = 1;
	prevCombo = 0;
	prevEnemyScore = 0;
	prevGateScore = 0;

	DEBUG_MSG("Level Created");

	initialTicks = SDL_GetTicks();

	SDL_DestroyTexture(textTure);
	SDL_DestroyTexture(textTure2);
	skyTrue = false;
	//conMan->LoadTexture("../Textures/sky.png", "sky", 1200, 768, 1);

	transition = false;

	BeatDetector::Instance()->getSystem()->createSound("../Sound/threeTone2.mp3", FMOD_SOFTWARE, 0, &sfx1);

	BeatDetector::Instance()->getSystem()->playSound(FMOD_CHANNEL_FREE, sfx1, false, 0);

	trackVis = new TrackVisualizer(conMan, rend);
	trackVis->Load();

	parralaxPos1 = new Vector2D(0, 0);
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
	delete BeatDetector::Instance();
}
void Level::Update(SDL_DisplayMode window)
{


	//COMBO STUFF STARTS IN
	prevScore = finalScore;
	prevEnemyScore = enemyManager->getEnemyScore();
	prevGateScore = player->playerScore;
	
	if ((SDL_GetTicks() - initialTicks) > 1200)
	{
		BeatDetector::Instance()->setStarted(true);
		BeatDetector::Instance()->update();
		trackVis->Update(window);
	}

	//conMan->Update();
	player->Update(window);
	turret->Update(player);
	gateManager->Update(player, window, finalCombo);
	enemyManager->Update(player, turret, finalCombo);

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
	else if (finalCombo == 3)
	{
		activeComboColor = yellow;
	}
	else if (finalCombo == 4)
	{
		activeComboColor = orange;
	}
	else
	{
		activeComboColor = pink;
	}
		
	
	finalScore = ((player->playerScore + enemyManager->getEnemyScore()));


	if (finalScore < 0)
		finalScore = 0;

	s = std::to_string(finalScore);

	if (finalScore == 0)
		s.insert(0, "00000");
	else if (finalScore < 1000)
		s.insert(0, "000");
	else if (finalScore >= 1000 && finalScore < 10000)
		s.insert(0, "00");
	

	s2 = std::to_string(finalCombo);
	s2.insert(0, "x");

	t->message = s;
	t2->message = s2;

	prevCombo = finalCombo;


	//RESIZING
	if (window.w > 1400)
	{
		textRect.w = 160;
		textRect.h = 70;
		textRect.x = 50;
		textRect.y = 20;

		textRect2.x = 40;
		textRect2.y = 900;
		textRect2.w = 80;
		textRect2.h = 50;

		if (!skyTrue)
		{
			conMan->LoadTexture("../Textures/sky.png", "sky", window.w, window.h, 1);
			skyTrue = true;
			parralaxPos2 = new Vector2D(window.w, 0);
		}

	}

	
	if (trackVis->onePercent < 5)
	{
		if (trackVis->currentSeconds >(trackVis->songLengthInSeconds + 5))
		{
			//Maybe fade out?
			transition = true;

		}
	}
	else
	{
		if (trackVis->currentSeconds >(trackVis->songLengthInSeconds + trackVis->onePercent))
		{
			//Maybe fade out?
			transition = true;

		}
	}
	

	//Change parralax Position
	parralaxPos1->m_x-=4;
	parralaxPos2->m_x-=4;

	if (parralaxPos1->m_x < -window.w)
	{
		parralaxPos1->m_x = window.w;
	}
	if (parralaxPos2->m_x < -window.w)
	{
		parralaxPos2->m_x = window.w;
	}
	//t->setMessage(s);
	//t->Update();
}

void Level::Draw()
{
	//DrawSky
	conMan->DrawTexture("sky", parralaxPos1, SDL_FLIP_NONE);
	conMan->DrawTexture("sky", parralaxPos2, SDL_FLIP_NONE);


	player->Draw();
	turret->Draw();
	enemyManager->Draw();
	gateManager->Draw();
	trackVis->Draw();

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

bool Level::readyToTransition()
{
	return transition;
}

int Level::getHighScore()
{
	return finalScore;
}

bool Level::transOut()
{
	//while (transPos->m_x < 0)
		//transPos->m_x += 10;

	return true;
}

bool Level::transIn()
{
	return true;
}