#pragma once
#include "NPC.h"

class Archer : public NPC
{
private:

public:
	Archer();
	Archer(const NPC& archer);
	~Archer();

	void Update(float dt, Army& enemyArmy);
};

