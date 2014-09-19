#pragma once
#ifndef BattleScene_HPP
#define BattleScene_HPP

#include <queue>
#include <UtH/UtHEngine.hpp>
#include "NPC.h"

class BattleScene : public uth::Scene
{
	private:
		uth::Shader m_shader;
		uth::GameObject* tower;
		std::vector<NPC*> enemies;
		uth::GameObject* selected;
		float timeCount;
		float zoomLevel;

		pmath::Vec2 lastStatPos;		// Last stationary touch position, change whenever there's a STATIONARY event after a NONE event
		bool dragging;

	public:
		BattleScene();
		~BattleScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(float dt);
		virtual bool Draw();

		void OnClick();
		void OnDrag();
		void ZoomIn();
		void ZoomOut();

		bool IsContained(pmath::Vec2 pos, uth::GameObject& obj);
		uth::GameObject* ContainsObject(pmath::Vec2 pos);
};

#endif

