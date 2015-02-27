#include "GateManager.h"

GateManager::GateManager(SDL_Renderer* r, ContentManager* c)
{
	renderer = r;
	maxGates = 4;
	currentGates = 0;
	renderer = r;
	conMan = c;
	g = new Gate(conMan, 900);
	g->Load();
	gateCombo = 1;
	increase = 50;
}

GateManager::~GateManager()
{
	delete g;
	delete renderer;
	delete conMan;
	delete lastBeat;
}

void GateManager::Update(Player* player, SDL_DisplayMode window, int finalCombo)
{
	//Logic for adding a new Gate...
	

	if (lastBeat != BeatDetector::Instance()->getLastBeat())
	{
		Add(window);
		DEBUG_MSG("BOOM BEAT IN GAME");
	}


	//What happens to all gates we have spawned
	for (std::size_t i = 0; i < gates.size(); i++)
	{
		gates.at(i)->Update();


		//MAKE COLLISION BOXES
		SDL_Rect a;
		a.x = (int)player->position->GetX() + 5;
		a.y = (int)player->position->GetY() + 5;
		a.w = player->width - 5;
		a.h = player->height - 5;

		SDL_Rect b;
		b.x = (int)gates.at(i)->gate1->position->m_x;
		b.y = (int)gates.at(i)->gate1->position->m_y;
		b.w = gates.at(i)->gate1->width;
		b.h = gates.at(i)->gate1->height;

		SDL_Rect c;
		c.x = (int)gates.at(i)->gate2->position->m_x;
		c.y = (int)gates.at(i)->gate2->position->m_y;
		c.w = gates.at(i)->gate2->width;
		c.h = gates.at(i)->gate2->height;

		if (TheCollision::Instance()->CheckCollision(a, b) && gates.at(i)->getAlive()== true)
		{
			gates.at(i)->setAlive(false);
			DEBUG_MSG("Silly billy");
			player->getHit();

			if (player->playerScore != 0)
			{
				player->playerScore -= 500;
				gateCombo=1;
			}
				
		}
		else if (TheCollision::Instance()->CheckCollision(a, c) && gates.at(i)->getAlive() == true)
		{
			gates.at(i)->setAlive(false);
			DEBUG_MSG("Silly billy");
			player->getHit();

			if (player->playerScore != 0)
			{
				player->playerScore -= 500;
				gateCombo=1;
			}
				
		}
		else if ((TheCollision::Instance()->CheckCollision(a, gates.at(i)->openGate) && gates.at(i)->getAlive() == true))
		{
			gates.at(i)->setAlive(false);
			DEBUG_MSG("Score Plus");
			player->playerScore += increase;

			if (gateCombo<20)
				gateCombo++;
		}

		if (gateCombo <= 1)
			finalCombo = 0;

		//Destroy
		if (gates.at(i)->getX() < -160)
		{
			//gates.at(i)->~Gate();
			gates.erase(gates.begin() + i);
			

			currentGates -= 1;
		}
	}


	increase = finalCombo * 50;


	lastBeat = BeatDetector::Instance()->getLastBeat();
}

void GateManager::Draw()
{
	for (std::size_t i = 0; i < gates.size(); i++)
	{
		gates.at(i)->Draw();
	}
}

// create a new gate
void GateManager::Add(SDL_DisplayMode window)
{
	currentGates += 1;

	//g->Load();
	gates.push_back(new Gate(conMan, window.w));
}

int GateManager::getCombo()
{
	if (gateCombo > 0)
		return gateCombo;
	else
		return 0;
}

