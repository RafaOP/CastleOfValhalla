#pragma once

#include <UtH/Engine/GameObject.hpp>
class Army;

class NPC : public uth::GameObject
{
	protected:
		float attack;
		float health;
		float attackRate;
		float xRange;
		float yRange;
		float speed;
		float cost;
		int level;
		float attackTimer;

		NPC* target;
		int direction;

	public:
		NPC(float attack = 10, float health = 10, float sRate = 2.f, float aRate = 1.f, float speed = 1.f, float xrange = 10.f, float yrange = 10.f, int level = 1, float cost = 0);
		NPC(const NPC& npc);
		~NPC();

		void setBaseAttack(float attack);
		void setBaseHealth(float health);
		void setAttackRate(float sRate);
		void setXRange(float range);
		void setYRange(float range);
		void setSpeed(float speed);
		void setCost(float cost);
		void setLevel(int level);

		float getBaseAttack() const;
		float getBaseHealth() const;
		float getAttack() const;
		float getHealth() const;
		float getAttackRate() const;
		float getXRange() const;
		float getYRange() const;
		float getSpeed() const;
		float getCost() const;
		int   getLevel() const;

		void attackNearest(float dt, Army& enemyArmy);
		void Update(float dt, Army& enemyArmy);
		void attackNPC(NPC* npc);
		float takeDamage(float damage);

		//NPC& operator=(const NPC& npc);
};