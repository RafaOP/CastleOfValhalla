#include "../include/Barrack.h"


Barrack::Barrack(int max, float time)
{
	maxSoldiers = max;
	this->time = time;
	respawnNow = false;
	spawned = 0;
	timer = 0;
}

Barrack::~Barrack() { delete model; }

void Barrack::setSoldierType(SOLDIER t) { type = t; }
void Barrack::setModelNPC(NPC* model) { this->model = model; }
SOLDIER Barrack::getSoldierType() { return type; }
NPC* Barrack::getModelNPC() { return model; }

void Barrack::Update(float dt)
{
	if (time < 0.f) return;
	if (spawned < maxSoldiers) timer += dt;
	if (timer >= time) respawnNow = true;
}

bool Barrack::RespawnNow()
{
	if (respawnNow)
	{
		respawnNow = false;
		timer = 0;
		return true;
	}

	return false;
}

void Barrack::setSpawned(int spawned) { this->spawned = spawned; }
void Barrack::setMaxSoldiers(int max) { maxSoldiers = max; }
void Barrack::setRespawnTime(float time) { this->time = time; }

int Barrack::getSpawned() { return spawned; }
int Barrack::getMaxSoldiers() { return maxSoldiers; }
float Barrack::getRespawnTime() { return time; }