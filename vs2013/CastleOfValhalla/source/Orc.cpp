#include "../include/Orc.h"
#include "../include/Army.h"
using namespace std;

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/Sprite.hpp>

Orc::Orc()
{
	uth::Texture* t = uthRS.LoadTexture("orc.tga");
	AddComponent(new uth::Sprite(t));
	transform.SetScale(0.06f);
	transform.SetPosition(0, 0);

	attack = 3;
	health = 15;
	attackRate = 1;
	xRange = 32;
	yRange = 32;
	speed = 128;
	level = 1;

	cost = 0;
	direction = 1;

	attackTimer = 0;
	target = nullptr;
}

Orc::Orc(const NPC& orc) : NPC(orc)
{
	uth::Texture* t = uthRS.LoadTexture("orc.tga");
	AddComponent(new uth::Sprite(t));
	transform.SetScale(0.06f);

	direction = 1;
}

Orc::~Orc()
{
}

// Walks toward the castle and kills everything in the way
void Orc::Update(float dt, Army& enemyArmy)
{
	attackNearest(dt, enemyArmy);

	static pmath::Vec2 spos = transform.GetPosition();
	if (!target)
	{
		pmath::Vec2 p = transform.GetPosition();
		direction = (spos.x <= 0 ? 1 : -1);
		transform.SetPosition(p.x + direction * speed * dt, p.y);
	}
}