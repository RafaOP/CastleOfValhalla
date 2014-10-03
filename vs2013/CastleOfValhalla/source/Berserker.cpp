#include "../include/Berserker.h"
#include "../include/Army.h"
using namespace std;

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/Sprite.hpp>

Berserker::Berserker()
{
	uth::Texture* t = uthRS.LoadTexture("warrior.png");
	AddComponent(new uth::Sprite(t));
	transform.SetScale(0.06f);
	transform.SetPosition(0, 0);

	attack = 1;
	health = 150;
	attackRate = 2;
	xRange = 32;
	yRange = 32;
	speed = 0;
	level = 1;

	cost = 12;
	direction = 0;

	attackTimer = 0;
	target = nullptr;
}

Berserker::Berserker(const NPC& berserker) : NPC(berserker)
{
	uth::Texture* t = uthRS.LoadTexture("warrior.png");
	AddComponent(new uth::Sprite(t));
	transform.SetScale(0.06f);
}

Berserker::~Berserker()
{
}

// Stands in position beating every enemy that comes close
void Berserker::Update(float dt, Army& enemyArmy)
{
	attackNearest(dt, enemyArmy);
}