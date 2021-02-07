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
void FollowCameraNode::SetTrackingArea(float inXLimit,float inYLimit)
{
	xLimit = inXLimit;
	yLimit = inYLimit;
}
void FollowCameraNode::SetSpeed(float speed)
{
	speedMultiplier = speed;
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

	if(xDifference>xLimit)
	{
		move((float)deltaTime * speedMultiplier *(xDifference - xLimit), 0.0f);
	}
	if(xDifference<-xLimit)
	{
		move((float)deltaTime * speedMultiplier * (xDifference + xLimit), 0.0f);
	}
	if(yDifference>yLimit)
	{
		move(0.0f, (float)deltaTime * speedMultiplier * (yDifference - yLimit));
	}
	if(yDifference<-yLimit)
	{
		move(0.0f,(float)deltaTime * speedMultiplier * (yDifference + yLimit));
	}
}
//Zoom funtion for the camera.
void FollowCameraNode::ZoomCamera()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		setScale(0.5, 0.5);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		setScale(1.0, 1.0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		setScale(2.0, 2.0);
	}
}
