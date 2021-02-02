#include"followcameranode.h"

#include<iostream>
//This function sets the cameras targetnode checking that what was sent in was not a nullptr before assigning it as target
void FollowCameraNode::SetTarget(std::shared_ptr<gbh::Node> inTarget)
{
	if(inTarget==nullptr)
	{
		return;
	}
	target = inTarget;
}
//Here we call the function that repeatedly check if we are 
void FollowCameraNode::onUpdate(double deltaTime)
{
	CheckCameraPlayerRelation(deltaTime);
}
//Function that check the relationship between where the player and camera is in the game telling the camera to follow the player if
//outside a set range. Basically we want to keep the player in the middle of the screen all the time.
void FollowCameraNode::CheckCameraPlayerRelation(double deltaTime)
{
	if(target==nullptr)
	{
		return;
	}

	float xDifference = target->getPosition().x - this->getPosition().x;
	float yDifference = target->getPosition().y - this->getPosition().y;

	float xLimit = 250.0f;
	float yLimit = 150.0f; 

	if(xDifference>xLimit)
	{
		move((float)deltaTime * 2 *(xDifference - xLimit), 0.0f);
	}
	if(xDifference<-xLimit)
	{
		move((float)deltaTime * 2 * (xDifference + xLimit), 0.0f);
	}
	if(yDifference>yLimit)
	{
		move(0.0f, (float)deltaTime * 2 * (yDifference - yLimit));
	}
	if(yDifference<-yLimit)
	{
		move(0.0f,(float)deltaTime * 2 * (yDifference + yLimit));
	}
}
