#pragma once
#include "sfml-engine/spritenode.h"
#include "sfml-engine/physics/physicsbody.h"
#include "sfml-engine/physics/physicscontact.h"

class CheckPoint: public gbh::SpriteNode
{
protected:
	
public:
	CheckPoint(const std::string& filename);
	void PlaceCeckpoint(sf::Vector2f & position);
	void ToggleOnOff(bool activate);
private:
	//variables	
	bool active;

};