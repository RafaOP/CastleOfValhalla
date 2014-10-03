#include "../include/Archer.h"

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/Sprite.hpp>

Archer::Archer()
{
	/*uth::Texture* t = uthRS.LoadTexture("archer.png");
	AddComponent(new uth::Sprite(t));
	transform.SetScale(0.02f);*/

	attack = 3;
	health = 100;
	attackRate = 3;
	xRange = 256;
	yRange = 256;
	speed = 0;
	level = 1;

	cost = 10;
	direction = 0;

	attackTimer = 0;
	target = nullptr;
}

Archer::Archer(const NPC& archer) : NPC(archer)
{
	/*uth::Texture* t = uthRS.LoadTexture("archer.png");
	AddComponent(new uth::Sprite(t));
	transform.SetScale(0.02f);*/
}

Archer::~Archer()
{
}

// Stands in position attacking everything that comes to it's range
void Archer::Update(float dt, Army& enemyArmy)
{
}