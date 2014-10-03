#pragma once

#include <UtH/Engine/GameObject.hpp>
#include "NPC.h"
#include <vector>

enum SOLDIER
{
	ARCHER,
	BERSERKER,
	ORC
};

class Barrack : public uth::GameObject
{
private:
	SOLDIER type;
	NPC* model;

	int spawned;
	int maxSoldiers;		// Max of soldiers spawned at the same time
	float time;				// Time to wait until next soldier is respawned
	float timer;

	bool respawnNow;

public:
	Barrack(int max = 5, float time = -1.f);
	~Barrack();

	void setSoldierType(SOLDIER t);
	void setModelNPC(NPC* model);
	SOLDIER getSoldierType();
	NPC* getModelNPC();

	void Update(float dt);
	bool RespawnNow();

	void setSpawned(int spawned);
	void setMaxSoldiers(int max);
	void setRespawnTime(float time);

	int getSpawned();
	int getMaxSoldiers();
	float getRespawnTime();
};
