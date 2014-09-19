#include "../include/Orc.h"


Orc::Orc()
{
	setAttack(5); //level 1 orc is 10 * setAttack = 50
	setHealth(10); //level 1 arher is 10 * setHealth = 100
	setSpawnRate(0.1);
	setAttackRate(0.5);
	setSpeed(5);
}


Orc::~Orc()
{
}
