#pragma once
#include<vector>
#include"sfml-engine/spritenode.h"
#include"sfml-engine/physics/physicsbody.h"

#include"checkpoint.h"

class AiControlledShip: public gbh::SpriteNode
{	
public:
	AiControlledShip(const std::string fileName);
	void MoveTowerds();
	void AssignListOfCheckpoints(std::vector<std::shared_ptr<CheckPoint>> inCheckpoint);
	void FindNewCeckPoint();
private:
	//variables
	std::shared_ptr<CheckPoint> currentCheckpoint;
	sf::Vector2f direction;	
    float speed = 1500.0f;//speed we use as force for the enemy ship/agent
	float reachingDistance = 2;
	int checkIndex = -1;
	std::vector<std::shared_ptr<CheckPoint>> checkpointsInScene;
	
};