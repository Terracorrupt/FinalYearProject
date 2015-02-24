#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* r, ContentManager* c)
{
	renderer = r;
	maxEnemies = 4;
	currentEnemies = 0;
	renderer = r;
	conMan = c;
	g = new Enemy(conMan);
	g->Load();
	lastBeat = BeatDetector::Instance()->getLastBeat();
	lastTickSpawned = 0;
	maxEnemies = 8;
	enemyScore = 0;
	enemyCombo = 1;
}

EnemyManager::~EnemyManager()
{
	delete g;
	delete conMan;
	delete renderer;
	delete lastBeat;
	delete(conMan->textures["enemy"]);
}

void EnemyManager::Update(Player* player, Turret* turret)
{

	rand3 = rand() % 4;


	//Testing....
	if ((SDL_GetTicks() - lastTickSpawned) > (1000-rand3*50))
	{
		if (enemies.size() < maxEnemies)
			Add();

		lastTickSpawned = SDL_GetTicks();
	}

	
	//Update each enemy
	for (std::size_t i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->Update();

		//Brute force movement
		// tell enemies to move towards player
		
		SDL_Rect a;
		a.x = (int)enemies.at(i)->position->GetX() + 5;
		a.y = (int)enemies.at(i)->position->GetY() + 5;
		a.w = enemies.at(i)->width - 5;
		a.h = enemies.at(i)->height - 5;

		SDL_Rect c;
		c.x = (int)player->position->GetX() + 5;
		c.y = (int)player->position->GetY() + 5;
		c.w = player->width - 5;
		c.h = player->height - 5;

		//Check against each bullet active
		//DEBUG_MSG(turret->bullets.size());
		DEBUG_MSG(enemies.size());

		for (std::size_t j = 0; j < turret->bullets.size(); j++)
		{
			SDL_Rect b;
			b.x = turret->bullets.at(j)->position->m_x;
			b.y = turret->bullets.at(j)->position->m_y;
			b.w = turret->bullets.at(j)->width;
			b.h = turret->bullets.at(j)->height;

			if ((TheCollision::Instance()->CheckCollision(a, b)) && enemies.at(i)->alive == true)
			{
				enemies.at(i)->alive = false;
				currentEnemies -= 1;
				enemyScore += 100;
				enemyCombo++;
			}
		}

		if ((TheCollision::Instance()->CheckCollision(a, c)) && enemies.at(i)->alive == true)
		{
			enemies.at(i)->alive = false;

			currentEnemies -= 1;
			enemyScore -= 100;
			enemyCombo = 1;
		}

		if (enemies.at(i)->alive == false)
		{
			enemies.erase(enemies.begin() + i);

		}
		else if (enemies.at(i)->position->m_x > 1500 || enemies.at(i)->position->m_x < -40 || enemies.at(i)->position->m_y > 1000 || enemies.at(i)->position->m_y < -100)
		{
			enemies.erase(enemies.begin() + i);

			currentEnemies -= 1;
		}

	}

	lastBeat = BeatDetector::Instance()->getLastBeat();
}

void EnemyManager::Draw()
{
	for (std::size_t i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->Draw();
	}
}

// create a new gate
void EnemyManager::Add()
{
	currentEnemies += 1;

	Enemy *e = new Enemy(conMan);

	rand1 = rand() % 300 + 700;
	rand2 = rand() % 600 + 100;

	e->Initialize(new Vector2D(rand1, rand2));

	//g->Load();
	enemies.push_back(e);
}

int EnemyManager::getEnemyScore()
{
	if (enemyScore > 0)
		return enemyScore;
	else
		return 0;
}
int EnemyManager::getCombo()
{
	if (enemyCombo > 0)
		return enemyCombo;
	else
		return 0;
}

void EnemyManager::setCombo(int co)
{
	enemyCombo = co;
}