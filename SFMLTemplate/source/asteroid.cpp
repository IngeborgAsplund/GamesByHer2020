#include "asteroid.h"
//Asteroid constructor
Asteroid::Asteroid(const std::string &imageName):gbh::SpriteNode(imageName)
{
	setName("asteroid");
}

void Asteroid::SetUpAsteroid(sf::Vector2f placement)
{
	setOrigin(0.5, 0.5);
	setPosition(placement.x, placement.y);
	getPhysicsBody()->setType(gbh::PhysicsBodyType::Dynamic);
	getPhysicsBody()->setAngularDamping(0);
	getPhysicsBody()->applyTorque(20.0f, true);
}