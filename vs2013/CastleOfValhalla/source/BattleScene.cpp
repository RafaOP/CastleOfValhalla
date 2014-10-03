#include "../include/BattleScene.h"
#include "../include/Orc.h"
#include "../include/Berserker.h"
#include <math.h>

#include <UtH/UtHEngine.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Core/Randomizer.hpp>
using namespace uth;

#ifdef UTH_SYSTEM_WINDOWS
#include <Windows.h>
#endif

bool BattleScene::Init()
{
#ifdef UTH_SYSTEM_WINDOWS
	SetWindowPos(GetConsoleWindow(), 0, 1420, 600, 600, 400, SWP_SHOWWINDOW);
#endif

	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	dragging = false;

	tower = new GameObject();
	Texture *t = uthRS.LoadTexture("tower.png");
	tower->AddComponent(new Sprite(t));
	tower->transform.SetScale(0.2f);

	zoomLevel = 1;
	selected = nullptr;
	lastStatPos = uthEngine.GetWindowResolution() / 2;

	// Set the barracks in the armies
	// Player barrack with 5 berserkers
	Barrack* b = new Barrack();
	b->setSoldierType(BERSERKER);
	b->setModelNPC(new Berserker());
	playerArmy.addBarrack(b, 5);

	float npcPos = 0 - 128 * 2;
	for (auto& i : playerArmy.getSoldiers())
	{
		i->transform.SetPosition(npcPos, i->transform.GetPosition().y);
		npcPos += 128;
	}

	for (auto& i : playerArmy.getSoldiers())
	{
		pmath::Vec2 p = i->transform.GetPosition();
		std::cout << "Base health is " << i->getBaseHealth() << std::endl;
	}

	// Enemy barrack with 5 orcs
	b = new Barrack();
	b->setSoldierType(ORC);
	b->setModelNPC(new Orc());
	enemyArmy.addBarrack(b, 5);
	
	npcPos = -uthEngine.GetWindowResolution().x / 2;
	for (auto& i : enemyArmy.getSoldiers())
	{
		i->transform.SetPosition(npcPos, i->transform.GetPosition().y);
		npcPos -= 128;
	}

	return true;
}

bool BattleScene::DeInit() { delete tower; return true; }

bool BattleScene::Update(float dt)
{
	playerArmy.Update(dt, enemyArmy);
	enemyArmy.Update(dt, playerArmy);

	if (uthInput.Common.Event() == uth::InputEvent::NONE) { dragging = false; }
	if (uthInput.Common.Event() == uth::InputEvent::STATIONARY) { if (!dragging) lastStatPos = uthInput.Common.Position(); }
	if (uthInput.Common.Event() == uth::InputEvent::CLICK) { OnClick(); }
	if (uthInput.Common.Event() == uth::InputEvent::DRAG) { OnDrag(); }
	if (uthInput.Common.Event() == uth::InputEvent::ZOOM_IN) { ZoomIn(); }
	if (uthInput.Common.Event() == uth::InputEvent::ZOOM_OUT) { ZoomOut(); }

	return true;
}

bool BattleScene::Draw()
{
	uthEngine.GetWindow().Clear();
	tower->Draw(uthEngine.GetWindow());
	enemyArmy.Draw(uthEngine.GetWindow());
	playerArmy.Draw(uthEngine.GetWindow());

	return true;
}

void BattleScene::OnClick()
{
	selected = ContainsObject(uthEngine.GetWindow().pixelToCoords(uthInput.Common.Position()));
	pmath::Vec2 pos = uthInput.Common.Position();
	WriteLog("CLICK PIXEL    X: %f, Y: %f\n", pos.x, pos.y);
	pos = uthEngine.GetWindow().pixelToCoords(pos);
	WriteLog("CLICK COORD    X: %f, Y: %f\n", pos.x, pos.y);
}

void BattleScene::OnDrag()
{
	pmath::Vec2 pos = uthInput.Common.Position();

	if (selected == tower && !dragging)
	{
		WriteLog("TOWER IS MOVING\n");
		// It moves in a grid
		pos -= uthEngine.GetWindowResolution() / 2;
		pos.x = ceil(pos.x / 64) * 64;
		pos.y = ceil(pos.y / 64) * 64;
		tower->transform.SetPosition(pos);
	}

	// If there's nothing selected, then move the camera
	if (!selected)
	{
		dragging = true;

		pos = pos - lastStatPos;
		pos = pos.normalize() * 4;
		// X is positive when moving right
		// Y is positive when moving down
		if (!(uthEngine.GetWindow().GetCamera().GetPosition().x <= -uthEngine.GetWindowResolution().x / (6 / zoomLevel)))
			if (pos.x < 0) uthEngine.GetWindow().GetCamera().Scroll(pos.x, 0);	// I can move left whenever the camera is not all to the left
		if (!(uthEngine.GetWindow().GetCamera().GetPosition().y <= -uthEngine.GetWindowResolution().x / (6 / zoomLevel)))
			if (pos.y < 0) uthEngine.GetWindow().GetCamera().Scroll(0, pos.y);	// I can move up whenever the camera is not all to he top
		if (!(uthEngine.GetWindow().GetCamera().GetPosition().x >= uthEngine.GetWindowResolution().x / (6 / zoomLevel)))
			if (pos.x > 0) uthEngine.GetWindow().GetCamera().Scroll(pos.x, 0);	// I can move right whenever the camera is not all to the right
		if (!(uthEngine.GetWindow().GetCamera().GetPosition().y >= uthEngine.GetWindowResolution().x / (6 / zoomLevel)))
			if (pos.y > 0) uthEngine.GetWindow().GetCamera().Scroll(0, pos.y);	// I can move down whenever the camera is not all to the bottom
	}
}

void BattleScene::ZoomIn()
{
	if (zoomLevel <= 3.f) // If it's already zoomed in
	{
		zoomLevel += 0.2f;
		uthEngine.GetWindow().GetCamera().SetZoom(zoomLevel);
		WriteLog("ZOOMED IN\n");
	}
}

void BattleScene::ZoomOut()
{
	if (zoomLevel >= 1.f) // If it's already zoomed out
	{
		zoomLevel -= 0.2f;
		uthEngine.GetWindow().GetCamera().SetZoom(zoomLevel);
		WriteLog("ZOOMED OUT\n");
	}
}

bool BattleScene::IsContained(pmath::Vec2 pos, GameObject& obj)
{
	const pmath::Rect bounds(obj.transform.GetPosition() - obj.transform.GetSize() *
		obj.transform.GetScale().x / 2.f, obj.transform.GetSize() * obj.transform.GetScale().x);

	return bounds.contains(pos);
}

// Select objects in the scene
// Ps.: soldiers don't count as objects
uth::GameObject* BattleScene::ContainsObject(pmath::Vec2 pos)
{
	if (IsContained(pos, *tower)) { WriteLog("TOWER SELECTED\n"); return tower; }

	return nullptr;
}

BattleScene::BattleScene() {}
BattleScene::~BattleScene() {}