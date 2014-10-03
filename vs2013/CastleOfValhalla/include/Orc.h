#pragma once
#include "NPC.h"
class Orc : public NPC
{
private:

public:
	Orc();
	Orc(const NPC& orc);
	~Orc();

	void Update(float dt, Army& enemyArmy);
};

