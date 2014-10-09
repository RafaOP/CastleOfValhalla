#include "../include/Archer.h"


Archer::Archer()
{
	setAttack(15); //level 1 arher is 10 * setAttack = 150
	setHealth(20); //level 1 arher is 10 * setHealth = 200
	setSpawnRate(0.1);
	setAttackRate(0.2);
	setSpeed(3);

}


Archer::~Archer()
{
}
