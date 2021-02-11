#pragma once
#include "sfml-engine/spritenode.h"
#include "sfml-engine/physics/physicsbody.h"
#include "sfml-engine/physics/physicscontact.h"

class Asteroid:public gbh::SpriteNode
{
public:
	Asteroid(const std::string &imageName);
	void SetUpAsteroid(sf::Vector2f placement);
};