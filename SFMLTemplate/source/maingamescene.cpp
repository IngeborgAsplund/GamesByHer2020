//include headerfile for this scriptfile
#include"maingamescene.h"
//include of standard c++ libraries
#include<iostream>
//engine specific includes.
#include"sfml-engine/game.h"
#include"sfml-engine/shapenode.h"
#include"sfml-engine/spritenode.h"
#include"sfml-engine/textnode.h"
#include"sfml-engine/mathutils.h"

//definition of used assets
const std::string kMainGameFont = "../assets/fonts/roboto-regular.ttf";
const std::string kMainGameBackground = "../assets/gfx/starfield-01.png";
const std::string KPlayerShip = "../assets/gfx/player-ship.png";
//On initialize scene method.
void MainGameScene::onInitializeScene()
{
	//load the font we want to use
	m_robotoFont.loadFromFile(kMainGameFont);

	//create the physics world
	Scene::createPhysicsWorld(sf::Vector2f(0.0f,0.0f));
	std::shared_ptr<gbh::Node> m_boudnaries = std::make_shared<gbh::Node>();//node that will hold the boundaries for the world
	m_boudnaries->setPhysicsBody(getPhysicsWorld()->createEdgeBox(sf::Vector2(1270.0f,710.0f)));
	m_boudnaries->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_boudnaries->setPosition(1280.0 / 2, 720.0 / 2);
	addChild(m_boudnaries);
	
	//create and add the background
	std::shared_ptr<gbh::SpriteNode> m_background = std::make_shared<gbh::SpriteNode>(kMainGameBackground);
	m_background->setName("Background");
	addChild(m_background);

	//create spaceship graphics
	std::shared_ptr<gbh::SpriteNode>m_playerShip = std::make_shared<gbh::SpriteNode>(KPlayerShip);
	m_playerShip->setName("Player");
	m_playerShip->setOrigin(0.5, 0.5);
	m_playerShip->setPosition(620, 500);
	m_playerShip->setScale(0.5, 0.5);

	sf::Vector2f shipsize = sf::Vector2f(55.0f, 102.0f);
	//Physics for player ship added
	m_playerShip->setPhysicsBody(getPhysicsWorld()->createBox(shipsize*0.5f));
	m_playerShip->getPhysicsBody()->setType(gbh::PhysicsBodyType::Dynamic);

	//damping and rotation for some reason not working in this version, and with these calls
	m_playerShip->getPhysicsBody()->setLinearDamping(1.0f);
	m_playerShip->getPhysicsBody()->setFixedRotation(true);

	addChild(m_playerShip);
}
void MainGameScene:: onUpdate(double deltaTime)
{
	captureInput();
}
void MainGameScene::captureInput() 
{
	std::shared_ptr<gbh::Node> player = getFirstChildWithName("Player",false);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		
	{		
		moveForce.y -= 1.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{		
		moveForce.y += 1.0;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{		
		moveForce.x -= 1.0;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{		
		moveForce.x += 1.0;
	}
	sf::Vector2f movement = moveForce * accelration;
	movement = gbh::math::normalize(movement);
	
}