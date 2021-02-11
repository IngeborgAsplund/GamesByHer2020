#include "checkpoint.h"

//checkpoints
CheckPoint::CheckPoint(const std::string& filename) :gbh::SpriteNode(filename)
{
	setName("checkPoint");
}
//getter for the bool active
bool CheckPoint::GetActive()
{
	return active;
}
//places the checkpoint in the world at a given position and sets the color to white semitransparent in order to mark them inactive
//it also 
void CheckPoint::PlaceCeckpoint(sf::Vector2f& position)
{
	setPosition(position);
	setOrigin(0.5, 0.5);
	setColor(sf::Color(255,255,255,64));
	getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	getPhysicsBody()->makeSensor();
	getPhysicsBody()->setEnabled(false);
	active = false;	
}
void CheckPoint::ToggleOnOff(bool activate)
{
	if(activate)
	{
		setColor(sf::Color(117, 124, 165, 192));
		getPhysicsBody()->setEnabled(true);
		active = true;
	}
	else
	{
		setColor(sf::Color(255, 255, 255, 64));
		getPhysicsBody()->setEnabled(false);
		active = false;
	}
}
void CheckPoint::MarkAsReached()
{
	if(active)
	{
		setColor(sf::Color(107, 182, 58,128));
		getPhysicsBody()->setEnabled(false);
	}
}