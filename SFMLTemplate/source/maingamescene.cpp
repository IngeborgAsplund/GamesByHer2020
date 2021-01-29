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
const std::string kMainMusic = "../assets/music/titlescreen.ogg";
const std::string kMainGameFont = "../assets/fonts/roboto-regular.ttf";
const std::string kMainGameBackground = "../assets/gfx/starfield-01.png";
const std::string kBigAsteroid = "../assets/gfx/asteroid-large-01.png";
const std::string kMediumAsteroid01 = "../assets/gfx/asteroid-medium-01.png";
const std::string kMediumAsteroid02 = "../assets/gfx/asteroid-medium-02.png";
const std::string kMediumAsteroid03 = "../assets/gfx/asteroid-medium-03.png";
const std::string KPlayerShip = "../assets/gfx/player-ship.png";
//On initialize scene method.
void MainGameScene::onInitializeScene()
{
	//load the font we want to use
	m_robotoFont.loadFromFile(kMainGameFont);
	m_mainMusic.openFromFile(kMainMusic);

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
	m_background->setOrigin(0.5f, 0.5f);
	m_background->setPosition(640, 300);
	addChild(m_background);
	//create and add some obstacles for the player to avoid


	//create spaceship graphics
	std::shared_ptr<gbh::SpriteNode>m_playerShip = std::make_shared<gbh::SpriteNode>(KPlayerShip);
	m_playerShip->setName("Player");
	m_playerShip->setOrigin(0.5, 0.5);
	m_playerShip->setPosition(620, 500);
	m_playerShip->setScale(0.5, 0.5);

	//Physics for player ship added
	sf::Vector2f shipsize = sf::Vector2f(55.0f, 102.0f);
	m_playerShip->setPhysicsBody(getPhysicsWorld()->createBox(shipsize*0.5f));
	m_playerShip->getPhysicsBody()->setType(gbh::PhysicsBodyType::Dynamic);
	m_playerShip->getPhysicsBody()->setLinearDamping(3.0f);
	m_playerShip->getPhysicsBody()->setFixedRotation(true);

	addChild(m_playerShip);
}
void MainGameScene:: onUpdate(double deltaTime)
{
	captureInput();
}
void MainGameScene::onShowScene()
{
	m_mainMusic.play();
	setDrawPhysicsDebug(true);
}
void MainGameScene::onHideScene()
{
	m_mainMusic.stop();
	setDrawPhysicsDebug(false);
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
	moveForce = gbh::math::normalize(moveForce);
	player->getPhysicsBody()->applyForceToCenter(moveForce*accelration);
	
}