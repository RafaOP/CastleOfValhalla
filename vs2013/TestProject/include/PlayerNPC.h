#pragma once

#include <UtH/Engine/GameObject.hpp>
#include "NPC.h"

class PlayerNPC : public NPC
{
	private:
		float cost;

	public:
		PlayerNPC();
		~PlayerNPC();
};