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
//Asteroids/obstacles
const std::string kBigAsteroid = "../assets/gfx/asteroid-large-01.png";
const std::string kMediumAsteroid01 = "../assets/gfx/asteroid-medium-01.png";
const std::string kMediumAsteroid02 = "../assets/gfx/asteroid-medium-02.png";
const std::string kMediumAsteroid03 = "../assets/gfx/asteroid-medium-03.png";
const std::string kSmallAsteroid01 = "../assets/gfx/asteroid-small-01.png";
const std::string kSmallAsteroid02 = "../assets/gfx/asterod-small-02";
//player character art
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
	//set up physics materials for asteroids
	gbh::PhysicsMaterial material_bigAsteroid;
	material_bigAsteroid.density = 3000;
	gbh::PhysicsMaterial material_mediumAsteroid;
	material_mediumAsteroid.density = 2000;
	//create and add some obstacles for the player to avoid
	std::shared_ptr<gbh::SpriteNode> m_asteroid1 = std::make_shared<gbh::SpriteNode>(kBigAsteroid);
	m_asteroid1->setOrigin(0.5f, 0.5f);
	m_asteroid1->setPosition(380, 200);
	m_asteroid1->setName("Asteroid1");
	m_asteroid1->setPhysicsBody(getPhysicsWorld()->createCircle(80.0f,material_bigAsteroid));
	m_asteroid1->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_asteroid1->getPhysicsBody()->setAngularDamping(0);
	m_asteroid1->getPhysicsBody()->applyTorque(20.0f, true);	
	addChild(m_asteroid1);
	rotatingObstacles.push_back(m_asteroid1);

	std::shared_ptr<gbh::SpriteNode> m_asteroid2 = std::make_shared<gbh::SpriteNode>(kMediumAsteroid01);
	m_asteroid2->setOrigin(0.5f, 0.5f);
	m_asteroid2->setPosition(830, 150);
	m_asteroid2->setName("Asteroid2");
	m_asteroid2->setPhysicsBody(getPhysicsWorld()->createCircle(40.0f, material_mediumAsteroid));
	m_asteroid2->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_asteroid2->getPhysicsBody()->setAngularDamping(0);
	m_asteroid2->getPhysicsBody()->applyTorque(20.0f, true);
	addChild(m_asteroid2);
	rotatingObstacles.push_back(m_asteroid2);

	std::shared_ptr<gbh::SpriteNode>m_asteroid3 = std::make_shared<gbh::SpriteNode>(kMediumAsteroid02);
	m_asteroid3->setOrigin(0.5f, 0.5f);
	m_asteroid3->setPosition(330, 450);
	m_asteroid3->setName("Asteroid3");
	m_asteroid3->setPhysicsBody(getPhysicsWorld()->createCircle(50.0f, material_mediumAsteroid));
	m_asteroid3->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_asteroid3->getPhysicsBody()->setAngularDamping(0);
	m_asteroid3->getPhysicsBody()->applyTorque(20.0f, true);
	addChild(m_asteroid3);
	rotatingObstacles.push_back(m_asteroid3);

	std::shared_ptr<gbh::SpriteNode>m_asteroid4 = std::make_shared<gbh::SpriteNode>(kMediumAsteroid03);
	m_asteroid4->setOrigin(0.5f, 0.5f);
	m_asteroid4->setPosition(770, 550);
	m_asteroid4->setName("Asteroid3");
	m_asteroid4->setPhysicsBody(getPhysicsWorld()->createCircle(40.0f, material_mediumAsteroid));
	m_asteroid4->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_asteroid4->getPhysicsBody()->setAngularDamping(0);
	m_asteroid4->getPhysicsBody()->applyTorque(20.0f, true);
	addChild(m_asteroid4);
	rotatingObstacles.push_back(m_asteroid4);

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
	RotateObstacles();
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
//This function takes each obstavle from the list of obstacles and rotate them by a rather low rotation amount this makes for
// rotating obstacles in the gameword
void MainGameScene::RotateObstacles()
{
	for(int i = 0; i< rotatingObstacles.size(); i++)
	{
		rotatingObstacles[i]->rotate(0.54f);
	}
}