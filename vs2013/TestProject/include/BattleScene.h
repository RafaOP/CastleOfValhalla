#pragma once
#ifndef BattleScene_HPP
#define BattleScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Physics/PhysicsWorld.hpp>
#include "NPC.h"
#include "Archer.h"
#include "Arrow.h"
#include "Berserker.h"
#include "Orc.h"

class BattleScene : public uth::Scene
{
	private:
		uth::Shader m_shader;
		uth::GameObject *tower;
		uth::GameObject *castle;
		Archer *archer1;
		Arrow *arrow1;
		Berserker *berserker1;
		Orc *orc1;
		std::vector<NPC*> enemies;
		float timeCount;
		float zoomLevel;

		uth::PhysicsWorld* world;

	public:
		BattleScene();
		~BattleScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(float dt);
		virtual bool Draw();

		bool IsContained(pmath::Vec2 pos, uth::GameObject& obj);
		uth::GameObject* ContainsObject(pmath::Vec2 pos);
};

#endif

