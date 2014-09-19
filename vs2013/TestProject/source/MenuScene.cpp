#include "../include/MenuScene.hpp"

#include <UtH/Engine/Engine.hpp>
#include <UtH/Platform/Debug.hpp> //WriteLog(...), works like printf.
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

using namespace uth;

// Main initialisation.
// Automatically called inside SceneManager.
bool MenuScene::Init()
{
	// Some shader must be loaded and set window to use it
	m_shader.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	m_shader.Use();
	uthEngine.GetWindow().SetShader(&m_shader);

	uth::Text* helloText = new Text("kenpixel.ttf", 24.f);

	helloGO = new GameObject();
	helloGO->AddComponent(helloText);

	helloText->AddText("Hello World!");
	helloGO->transform.SetPosition(0, -256.f);

	return true;
}

// Main deinitialisation.
// Automatically called inside SceneManager.
bool MenuScene::DeInit()
{
	delete helloGO;
	delete worldGO;
	return true;
}

// Update loop. Gone trought once per frame.
bool MenuScene::Update(float dt)
{
	return true; // Update succeeded.
}

// Draw loop. All graphics are drawn during this loop.
bool MenuScene::Draw()
{
	worldGO->Draw(uthEngine.GetWindow());
	helloGO->Draw(uthEngine.GetWindow());

	return true; // Drawing succeeded.
}

//Default constructor for initialising constant variables.
MenuScene::MenuScene()
{

}
//Default deconstrutor.
MenuScene::~MenuScene()
{

}