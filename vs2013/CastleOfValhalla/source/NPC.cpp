#include "../include/NPC.h"


NPC::NPC(float attack, float health, float sRate, float aRate, float speed, int level)
{
}


NPC::~NPC()
{
}

void NPC::setBaseAttack(float attack)    { this->attack = attack; }
void NPC::setBaseHealth(float health)    { this->health = health; }
void NPC::setSpawnRate(float aRate)  { this->spawnRate = aRate; }
void NPC::setAttackRate(float sRate) { this->attackRate = sRate; }
void NPC::setSpeed(float speed)      { this->speed = speed; }
void NPC::setLevel(int level)        { this->level = level; }

float NPC::getBaseAttack()     { return attack; }
float NPC::getBaseHealth()     { return health; }
float NPC::getAttack()     { return (level + 9) * attack; }
float NPC::getHealth()     { return (level + 9) * health; }
float NPC::getSpawnRate()  { return spawnRate; }
float NPC::getAttackRate() { return attackRate; }
float NPC::getSpeed()      { return speed; }
int   NPC::getLevel()      { return level; }

float NPC::TakeDamage(float attack)
{
	health = (getHealth() - attack) / (9 + level);
	return getHealth();
}

void NPC::Update(float dt) // Should receive another parameter with the positions of the enemy group
{
	pmath::Vec2 lastPos = transform.GetPosition();
}