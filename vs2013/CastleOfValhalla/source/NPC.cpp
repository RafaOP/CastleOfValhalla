#include "../include/NPC.h"
#include "../include/Army.h"
#include <iostream>
#include <cmath>
using namespace std;

NPC::NPC(float attack, float health, float sRate, float aRate, float speed, float xrange, float yrange, int level, float cost)
{
	setBaseAttack(attack);
	setBaseHealth(health);
	setAttackRate(aRate);
	setSpeed(speed);
	setXRange(xrange);
	setYRange(yrange);
	setLevel(level);
	setCost(cost);

	target = nullptr;
	attackTimer = 0;
	direction = 1;
}

NPC::NPC(const NPC& npc) : GameObject(npc)
{
	attack = npc.attack;
	health = npc.health;
	attackRate = npc.attackRate;
	speed = npc.speed;
	xRange = npc.xRange;
	yRange = npc.yRange;
	level = npc.level;

	cost = npc.cost;

	direction = 0;

	attackTimer = 0;
	target = nullptr;
}


NPC::~NPC()
{
}

void NPC::setBaseAttack(float attack)    { this->attack = attack; }
void NPC::setBaseHealth(float health)    { this->health = health; }
void NPC::setAttackRate(float sRate) { this->attackRate = sRate; }
void NPC::setXRange(float range)	 { xRange = range; }
void NPC::setYRange(float range)	 { yRange = range; }
void NPC::setSpeed(float speed)      { this->speed = speed; }
void NPC::setCost(float cost)		 { this->cost = cost; }
void NPC::setLevel(int level)        { this->level = level; }

float NPC::getBaseAttack() const     { return attack; }
float NPC::getBaseHealth() const     { return health; }
float NPC::getAttack() const		 { return (level + 9) * attack; }
float NPC::getHealth() const		 { return (level + 9) * health; }

float NPC::getAttackRate() const { return attackRate; }
float NPC::getXRange()	   const { return xRange; }
float NPC::getYRange()	   const { return yRange; }
float NPC::getSpeed()      const { return speed; }
float NPC::getCost()	   const { return cost; }
int   NPC::getLevel()      const { return level; }

float NPC::takeDamage(float damage)
{
	if (health <= 0.f) return 0;

	float h = getHealth();
	float aux = (h - damage) / (9 + level);
	health = aux;
	if (health <= 0)
	{
		cout << "NPC DEAD" << endl;
		setBaseAttack(0);
		setAttackRate(0);
	}

	return getHealth();
}

void NPC::attackNearest(float dt, Army& enemyArmy)
{
	attackTimer += dt;

	// If it's possible to attack now
	if (attackTimer >= 1 / attackRate)
	{
		vector<NPC*> soldiers = enemyArmy.getSoldiers();
		pmath::Vec2 pos = transform.GetPosition();
		float distance = xRange + 1.f;

		for (auto& enemy : soldiers)
		{
			// Calc the distance from soldier to enemy
			pmath::Vec2 epos = enemy->transform.GetPosition();
			//if (it == enemyArmy.army.begin()) distance = abs(pos.x - epos.x);
			// Finds the closest enemy
			if (abs(pos.x - epos.x) <= distance)
			{
				// If the target is not in a similar y level, ignore it
				if (!(pos.y + yRange >= epos.y && pos.y - yRange <= epos.y))
					continue;
				target = enemy;
				distance = abs(pos.x - epos.x);
			}
		}

		// Attack the closest enemy if it's distance is withing the attack range of the NPC
		// If 'target' is nullptr at this point. It shoudn't be. Definitely shouldn't.
		if (distance <= xRange)
		{
			attackNPC(target);
			attackTimer = 0;
		}
		// If it's not, then there's no target
		else target = nullptr;
	}
}

void NPC::Update(float dt, Army& enemyArmy) {}

// Play the animations and then attack
void NPC::attackNPC(NPC* npc)
{
	npc->takeDamage(getAttack());
}