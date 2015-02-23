#ifndef GATE_MANAGER_H
#define GATE_MANAGER_H

#include "Gate.h"
#include <vector>
#include "Player.h"
#include "BeatDetector.h"
#include "TimeStamp.h"
#include "Collision.h"

class GateManager
{
public:
	GateManager(SDL_Renderer* r, ContentManager* c);
	~GateManager();
	void Update(Player* player);
	void Draw();
	void Add();
	int getCombo();
	void setCombo(int);
	vector<Gate*> gates;
	SDL_Renderer* renderer;
	ContentManager* conMan;
	int maxGates;
	int currentGates;
	TimeStamp* lastBeat;
	Gate* g;
	int gateCombo;
};

#endif