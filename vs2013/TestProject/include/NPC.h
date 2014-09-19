#pragma once

#include <UtH/Engine/GameObject.hpp>

class NPC : public uth::GameObject
{
	private:
		float attack;
		float health;
		float spawnRate;
		float attackRate;
		float speed;
		int level;

	public:
		NPC(float attack = 10, float health = 10, float sRate = 2.f, float aRate = 1.f, float speed = 1.f, int level = 10);
		~NPC();

		void setAttack(float attack);
		void setHealth(float health);
		void setSpawnRate(float aRate);
		void setAttackRate(float sRate);
		void setSpeed(float speed);
		void setLevel(int level);

		float getAttack();
		float getHealth();
		float getSpawnRate();
		float getAttackRate();
		float getSpeed();
		int   getLevel();

		void Update(float dt);
};