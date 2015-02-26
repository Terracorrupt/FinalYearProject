#include "Gate.h"

Gate::Gate(ContentManager* c, int w)
{
	gate1 = new LargeGateObject(c,true);
	gate2 = new LargeGateObject(c,false);

	alive = true;
	
	Initialize(w);
}

Gate::~Gate()
{
	delete gate1;
	delete gate2;
	delete velocity;
}

void Gate::Initialize(int w)
{
	gate1->Initialize(9.0f);
	gate2->Initialize(9.0f);
	
	rand1 = rand() % 300 + 10;
	rand2 = -rand1;
	rand2 += 790;

	if (w > 1400)
	{
		gate1->SetSpawn(new Vector2D(w - 500, (-rand1 - 320)));
		gate2->SetSpawn(new Vector2D(w - 500, (rand2 + 320)));
	}
	else if (w < 1400 && w>800)
	{
		rand2 - 200;

		gate1->SetSpawn(new Vector2D(w - 500, (-rand1 - 320)));
		gate2->SetSpawn(new Vector2D(w - 500, (rand2 + 320)));
	}
		

	openGate.x = (int) gate1->position->m_x;
	openGate.w = (int) gate1->width;

	openGate.y = (int)gate1->position->m_y + gate1->height;
	openGate.h = (int)gate2->position->m_y - openGate.y;


}

void Gate::Load()
{
	gate1->Load();
	gate2->Load();
}

void Gate::Update()
{
	gate1->Update();
	gate2->Update();

	openGate.x = (int) gate1->position->m_x;
	openGate.w = (int) gate1->width;

	openGate.y = (int) gate1->position->m_y + gate1->height;
	openGate.h = (int)gate2->position->m_y - openGate.y;
}

void Gate::Draw()
{
	gate1->Draw();
	gate2->Draw();

}

float Gate::getX()
{
	return gate1->position->m_x;
}

void Gate::setAlive(bool b)
{
	alive = b;
}

bool Gate::getAlive()
{
	return alive;
}