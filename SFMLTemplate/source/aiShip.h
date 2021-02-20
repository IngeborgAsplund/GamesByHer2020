#pragma once
#include"sfml-engine/spritenode.h"
#include"sfml-engine/physics/physicsbody.h"

#include"checkpoint.h"

class AiControlledShip:public gbh::SpriteNode
{	
public:
	void MoveTowerds();
private:
	//variables
	std::shared_ptr<CheckPoint> currentCheckpoint;
    float speed = 4.0f;//speed we use as force for the enemy ship/agent
	bool reached = false;
	//functions
	void FindNewCeckPoint();
};