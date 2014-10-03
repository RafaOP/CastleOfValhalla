#pragma once

#include "NPC.h"
#include "Barrack.h"
#include <vector>
#include <unordered_map>

class Army
{
private:
	std::unordered_map< Barrack*, std::vector<NPC*> > army;

public:
	Army();
	~Army();

	void Update(float dt, Army& enemyArmy);
	void Draw(uth::RenderTarget& target);

	void addBarrack(Barrack* barrack, int numberNPCs = 0);

	std::vector<NPC*> getSoldiers();
};

