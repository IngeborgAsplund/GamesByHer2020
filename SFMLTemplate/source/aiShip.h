#pragma once
#include<vector>
#include"sfml-engine/spritenode.h"
#include"sfml-engine/physics/physicsbody.h"

#include"checkpoint.h"

class AiControlledShip:public gbh::SpriteNode
{	
public:
	void MoveTowerds();
	void AssignListOfCheckpoints(std::vector<std::shared_ptr<CheckPoint>> inCheckpoint);
private:
	//variables
	std::shared_ptr<CheckPoint> currentCheckpoint;
	sf::Vector2f direction;
    float speed = 4.0f;//speed we use as force for the enemy ship/agent
	int checkIndex = -1;
	bool reached = false;
	std::vector<std::shared_ptr<CheckPoint>> checkpointsInScene;
	//functions
	void FindNewCeckPoint();
};