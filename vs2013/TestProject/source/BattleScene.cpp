#include "../include/BattleScene.h"


#include <UtH/Engine/Engine.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Core/Randomizer.hpp>
using namespace uth;

#include <math.h>

bool BattleScene::Init()
{
	// Physics world
	world = new PhysicsWorld(0, 10);

	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	tower = new GameObject();
	Texture *t = uthRS.LoadTexture("tower.tga");
	tower->AddComponent(new Sprite(t));
	tower->transform.SetScale(0.2f);

	castle = new GameObject();
	Texture *ca1 = uthRS.LoadTexture("castle.tga");
	castle->AddComponent(new Sprite(ca1));
	castle->transform.SetScale(1.0f);

	archer1 = new Archer();
	archer1->setLevel(25);
	Texture *a1 = uthRS.LoadTexture("archer.tga");
	archer1->AddComponent(new Sprite(a1));
	archer1->transform.SetScale(0.06f);
	archer1->transform.SetPosition(-120, -200);
	WriteLog("archer level %i\n", archer1->getLevel());
	WriteLog("archer attack %f\n", archer1->getAttack());
	WriteLog("archer health %f\n", archer1->getHealth());
	WriteLog("archer spawnrate %f\n", archer1->getSpawnRate());
	WriteLog("archer attackrate %f\n", archer1->getAttackRate());
	WriteLog("archer speed %f\n", archer1->getSpeed());

	arrow1 = new Arrow();
	Texture *ar1 = uthRS.LoadTexture("test.tga");
	arrow1->AddComponent(new Sprite(ar1));
	//arrow1->transform.SetScale(0.01f);
	arrow1->transform.SetPosition(-100, -200);
	// Give a reference to rigidbody
	arrow1->AddComponent(new Rigidbody(*world));
	auto rb = arrow1->GetComponent<Rigidbody>("Rigidbody");
	rb->ApplyForce(pmath::Vec2(130, -300));
	//auto arrow1bounds = arrow1->transform.GetBounds();
	//orc1->transform.GetBounds().intersects(arrow1bounds);

	berserker1 = new Berserker();
	Texture *br1 = uthRS.LoadTexture("berserker.tga");
	berserker1->AddComponent(new Sprite(br1));
	berserker1->transform.SetPosition(250, 200);
	berserker1->transform.SetScale(0.1f);

	orc1 = new Orc();
	Texture *or1 = uthRS.LoadTexture("orc.tga");
	orc1->AddComponent(new Sprite(or1));
	orc1->transform.SetPosition(320, 200);
	orc1->transform.SetScale(0.06f);



	timeCount = 0;
	zoomLevel = 1;

	return true;
}
bool BattleScene::DeInit() { delete tower; delete castle; delete archer1; delete arrow1; delete world; return true; }

bool BattleScene::Update(float dt)
{
	timeCount += dt;

	if (timeCount - 1 >= 0)
	{
		NPC *enemy = new NPC();
		uth::Texture *t = uthRS.LoadTexture("warrior.tga");
		enemy->AddComponent(new uth::Sprite(t));
		enemy->transform.SetScale(0.06f);
		int side = (Randomizer::GetFloat(-1, 1) > 0 ? 1 : -1);
		enemy->transform.SetPosition(uthEngine.GetWindowResolution().x / 2 * side, 216.8 - enemy->transform.GetSize().y * 0.03f);
		enemies.push_back(enemy);
		
		timeCount = 0;
	}

	std::vector<NPC*>::iterator it = enemies.begin();
	
	while (it != enemies.end())
	{
		pmath::Vec2 pos = (*it)->transform.GetPosition();
		if (pos.x < -5)
		{
			(*it)->transform.SetPosition(pos.x + 2.f, pos.y);
			++it;
		}
		else if (pos.x > 5)
		{
			(*it)->transform.SetPosition(pos.x - 2.f, pos.y);
			++it;
		}
		else it = enemies.erase(it);
	}

	if (uthInput.Common.Event() == uth::InputEvent::CLICK)
	{
		for (std::vector<NPC*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		{
			if (IsContained(uthInput.Common.Position(), **it))
			{
				if (it != enemies.end() - 1)
					it = enemies.erase(it);
				else
				{
					enemies.erase(it);
					break;
				}
			}
		}
	}

	if (uthInput.Common.Event() == uth::InputEvent::DRAG)
	{
		pmath::Vec2 pos = uthInput.Common.Position();

		// If the tower is below the mouse position
		if (IsContained(pos, *tower))
		{
			pos -= uthEngine.GetWindowResolution() / 2;
			pos.x = ceil(pos.x / 64) * 64;
			pos.y = ceil(pos.y / 64) * 64;
			tower->transform.SetPosition(pos);
		}
	}

	//static float time = 0;
	//time += dt;
	//uthEngine.GetWindow().GetCamera().SetZoom(0);

	if (uthInput.Common.Event() == uth::InputEvent::ZOOM_IN)
	{
		if (zoomLevel <= 1.f) // If it's already zoomed in
		{
			zoomLevel += 0.1f;
			uthEngine.GetWindow().GetCamera().SetZoom(zoomLevel);
			WriteLog("ZOOMED IN\n");
		}
	}

	if (uthInput.Common.Event() == uth::InputEvent::ZOOM_OUT)
	{
		if (zoomLevel >= 0.4f) // If it's already zoomed out
		{
			zoomLevel -= 0.1f;
			uthEngine.GetWindow().GetCamera().SetZoom(zoomLevel);
			WriteLog("ZOOMED OUT\n");
		}
	}

	world->Update();
	arrow1->Update(dt);

	return true;
}
bool BattleScene::Draw()
{
	uthEngine.GetWindow().Clear();
	castle->Draw(uthEngine.GetWindow());
	tower->Draw(uthEngine.GetWindow());
	archer1->Draw(uthEngine.GetWindow());
	arrow1->Draw(uthEngine.GetWindow());
	berserker1->Draw(uthEngine.GetWindow());
	orc1->Draw(uthEngine.GetWindow());

	for (std::vector<NPC*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		(*it)->Draw(uthEngine.GetWindow());

	return true;
}

bool BattleScene::IsContained(pmath::Vec2 pos, GameObject& obj)
{
	pmath::Vec2 objPos = obj.transform.GetPosition();
	// FIX IN NEW ENGINE VERSION
	objPos.x += uthEngine.GetWindowResolution().x / 2;
	objPos.y += uthEngine.GetWindowResolution().y / 2;
	// END
	pmath::Vec2 size = obj.transform.GetSize();
	size.x *= obj.transform.GetScale().x;
	size.y *= obj.transform.GetScale().y;

	return (pos.x >= objPos.x - size.x && pos.x <= objPos.x + size.x &&
			pos.y >= objPos.y - size.y && pos.y <= objPos.y + size.y);
}

uth::GameObject* BattleScene::ContainsObject(pmath::Vec2 pos)
{
	for (std::vector<NPC*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		if (IsContained(pos, **it))
			return *it;
	if (IsContained(pos, *tower)) return tower;

	return nullptr;
}

BattleScene::BattleScene() {}
BattleScene::~BattleScene() {}