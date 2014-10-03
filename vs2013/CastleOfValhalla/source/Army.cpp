#include "../include/Army.h"
#include "../include/Archer.h"
#include "../include/Berserker.h"
#include "../include/Orc.h"
using namespace std;

Army::Army()
{
}


Army::~Army()
{
}

void Army::Update(float dt, Army& enemyArmy)
{
	for (auto& barrack : army)
	{
		barrack.first->Update(dt);
		for (auto& npc : barrack.second)
		{
			switch (barrack.first->getSoldierType())
			{
				case ARCHER:
					((Archer*)npc)->Update(dt, enemyArmy);
					break;
				case BERSERKER:
					((Berserker*)npc)->Update(dt, enemyArmy);
					break;
				case ORC:
					((Orc*)npc)->Update(dt, enemyArmy);
					break;
				default:
					npc->Update(dt, enemyArmy);
			}
		}
	}

	for (auto& barrack : army)
	{
		for (vector<NPC*>::iterator npc = barrack.second.begin(); npc != barrack.second.end(); ++npc)
		{
			if ((*npc)->getHealth() <= 0)
			{
				// Delete it and reduce the number of spawned in the barrack
				barrack.first->setSpawned(barrack.first->getSpawned() - 1);
				if (npc + 1 == barrack.second.end())
				{
					barrack.second.erase(npc);
					break;
				}
				else npc = barrack.second.erase(npc);
			}
		}

		if (barrack.first->RespawnNow())
		{
			// Respawn now and increase the number of soldiers in the barrack
			switch (barrack.first->getSoldierType())
			{
				case ARCHER:
					barrack.second.push_back(new Archer(*barrack.first->getModelNPC()));
					break;
				case BERSERKER:
					barrack.second.push_back(new Berserker(*barrack.first->getModelNPC()));
					break;
				case ORC:
					barrack.second.push_back(new Orc(*barrack.first->getModelNPC()));
					break;
				default:
					barrack.second.push_back(new NPC(*barrack.first->getModelNPC()));
			}
			barrack.first->setSpawned(barrack.first->getSpawned() + 1);
		}
	}
}

void Army::Draw(uth::RenderTarget& target)
{
	for (auto& i : army)
		for (auto& j : i.second)
			j->Draw(target);
}

void Army::addBarrack(Barrack* barrack, int numberNPCs)
{
	vector<NPC*> value;

	if (numberNPCs > barrack->getMaxSoldiers())
		numberNPCs = barrack->getMaxSoldiers();

	for (int i = 0; i < numberNPCs; ++i)
	{
		switch (barrack->getSoldierType())
		{
			case ARCHER:
				value.push_back(new Archer(*barrack->getModelNPC()));
				break;
			case BERSERKER:
				value.push_back(new Berserker(*barrack->getModelNPC()));
				break;
			case ORC:
				value.push_back(new Orc(*barrack->getModelNPC()));
				break;
			default:
				value.push_back(new NPC(*barrack->getModelNPC()));
		}
	}

	barrack->setSpawned(numberNPCs);
	army.insert(make_pair(barrack, value));
}

vector<NPC*> Army::getSoldiers()
{
	vector<NPC*> soldiers;

	for (auto& i : army)
		for (auto& j : i.second)
			soldiers.push_back(j);

	return soldiers;
}