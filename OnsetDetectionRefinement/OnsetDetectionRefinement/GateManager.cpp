#include "GateManager.h"

GateManager::GateManager(SDL_Renderer* r, ContentManager* c)
{
	renderer = r;
	maxGates = 4;
	currentGates = 0;
	renderer = r;
	conMan = c;
	g = new Gate(conMan);
	g->Load();
}

GateManager::~GateManager()
{
}

void GateManager::Update(Player* player)
{
	//Logic for adding a new Gate...
	

	if (lastBeat != BeatDetector::Instance()->getLastBeat())
	{
		Add();
		DEBUG_MSG("BOOM BEAT IN GAME");
	}


	//What happens to all gates we have spawned
	for (std::size_t i = 0; i < gates.size(); i++)
	{
		gates.at(i)->Update();

		if (gates.at(i)->getX() < -160)
		{
			//gates.at(i)->~Gate();
			gates.erase(gates.begin() + i);
			
			currentGates -= 1;
		}
	}

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
void GateManager::Add()
{
	currentGates += 1;

	g->Load();
	gates.push_back(new Gate(conMan));
}



