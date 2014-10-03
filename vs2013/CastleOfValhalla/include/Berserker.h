#pragma once
#include "NPC.h"

class Berserker : public NPC
{
private:

public:
	Berserker();
	Berserker(const NPC& berserker);
	~Berserker();

	void Update(float dt, Army& enemyArmy);
};

 