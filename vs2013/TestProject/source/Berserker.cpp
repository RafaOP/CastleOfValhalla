#include "../include/Berserker.h"


Berserker::Berserker()
{
	setAttack(10); //level 1 Berserker is 10 * setAttack = 100
	setHealth(30); //level 1 Berserker is 10 * setHealth = 300
	setSpawnRate(0.1);
	setAttackRate(0.5);
	setSpeed(5);
}


Berserker::~Berserker()
{
}
