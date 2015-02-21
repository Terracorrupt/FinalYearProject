#include "Gate.h"

Gate::Gate(ContentManager* c)
{
	gate1 = new LargeGateObject(c);
	gate2 = new LargeGateObject(c);

	Initialize();
}

Gate::~Gate()
{
	delete gate1;
	delete gate2;
}

void Gate::Initialize()
{
	gate1->Initialize(9.0f);
	gate2->Initialize(9.0f);
	
	rand1 = rand() % 300 + 10;
	rand2 = -rand1;
	rand2 += 620;

	gate1->SetSpawn(new Vector2D(900, -rand1));
	gate2->SetSpawn(new Vector2D(900, rand2));
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