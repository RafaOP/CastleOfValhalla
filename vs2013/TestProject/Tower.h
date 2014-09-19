#pragma once

#include <UtH/Engine/GameObject.hpp>

class Tower : public uth::GameObject
{
private:
	int level;


public:
	Tower();
	~Tower();
};

