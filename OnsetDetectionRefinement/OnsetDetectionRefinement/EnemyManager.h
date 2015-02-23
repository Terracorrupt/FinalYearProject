#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"
#include <vector>
#include "Player.h"
#include "Turret.h"
#include "BeatDetector.h"
#include "TimeStamp.h"
#include "Collision.h"
#include <random>

class EnemyManager
{
public:
	EnemyManager(SDL_Renderer* r, ContentManager* c);
	~EnemyManager();
	void Update(Player* player, Turret* turret);
	void Draw();
	void Add();
	int getEnemyScore();
	int getCombo();
	void setCombo(int);
	vector<Enemy*> enemies;
	SDL_Renderer* renderer;
	ContentManager* conMan;
	int maxEnemies;
	int currentEnemies;
	TimeStamp* lastBeat;
	int lastTickSpawned;
	int enemyScore;
	Enemy* g;
	int enemyCombo;
private:
	int rand1, rand2, rand3;
};

#endif