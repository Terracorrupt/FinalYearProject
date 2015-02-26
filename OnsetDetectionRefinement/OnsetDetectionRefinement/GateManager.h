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
	void Update(Player* player, SDL_DisplayMode d, int finalCombo);
	void Draw();
	void Add(SDL_DisplayMode);
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
	int increase;
};

#endif