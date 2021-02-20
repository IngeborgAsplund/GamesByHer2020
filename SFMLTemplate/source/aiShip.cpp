#include<string>
#include<iostream>
#include"sfml-engine/mathutils.h"
#include "sfml-engine/spritenode.h"

#include"aiShip.h"

AiControlledShip::AiControlledShip(const std::string fileName):gbh::SpriteNode(fileName)
{
	setName("Adversary");
}
//Give acess to the checkpoints we have in scene and assign the current checkpoint to the first one 
void AiControlledShip::AssignListOfCheckpoints(std::vector<std::shared_ptr<CheckPoint>> inCheckpoint)
{
	checkpointsInScene = inCheckpoint;
	checkIndex = 0;
	currentCheckpoint = checkpointsInScene[checkIndex];
	reached = false;
}

void AiControlledShip::FindNewCeckPoint()
{
	if(checkIndex>-1&&checkIndex< checkpointsInScene.size()-1)
	{
		checkIndex++;
		currentCheckpoint = checkpointsInScene[checkIndex];
		reached = false;
	}
}
void AiControlledShip::MoveTowerds()
{
	float xDirection = currentCheckpoint->getPosition().x-this->getPosition().x;
	float yDirection = currentCheckpoint->getPosition().y - this->getPosition().y;
	direction = gbh::math::normalize(sf::Vector2f(xDirection, yDirection));	
    getPhysicsBody()->applyForceToCenter(direction*speed);
	
	
}
