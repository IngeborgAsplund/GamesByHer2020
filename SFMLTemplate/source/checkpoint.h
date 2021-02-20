#pragma once
#include<string>
#include "sfml-engine/spritenode.h"
#include "sfml-engine/physics/physicsbody.h"
#include "sfml-engine/physics/physicscontact.h"

class CheckPoint: public gbh::SpriteNode
{
public:
	CheckPoint(const std::string& filename);
	bool GetActive();
	void PlaceCeckpoint(sf::Vector2f & position);
	void ToggleOnOff(bool activate);
	void MarkAsReached();//when we reach a checkpoint this should be called
private:
	//variables	
	bool active;

};