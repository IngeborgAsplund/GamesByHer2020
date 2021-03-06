//include headerfile for this scriptfile
#include"asteroid.h"
#include "gamestate.h"
#include"maingamescene.h"
//include of standard c++ libraries
#include<ctime>
#include<fstream>
#include<iostream>
#include<random>

//engine specific includes.
#include"sfml-engine/game.h"
#include"sfml-engine/shapenode.h"
#include"sfml-engine/spritenode.h"
#include"sfml-engine/textnode.h"
#include"sfml-engine/mathutils.h"

#include "nlohmann/json.hpp"

//definition of used assets
const std::string kMainMusic = "../assets/music/titlescreen.ogg";
const std::string kMainGameFont = "../assets/fonts/roboto-regular.ttf";
const std::string kBackGround = "../assets/gfx/starfield-01.png";
//Asteroids/obstacles
const std::string kBigAsteroid = "../assets/gfx/asteroid-large-01.png";
const std::string kMediumAsteroid01 = "../assets/gfx/asteroid-medium-01.png";
const std::string kMediumAsteroid02 = "../assets/gfx/asteroid-medium-02.png";
const std::string kMediumAsteroid03 = "../assets/gfx/asteroid-medium-03.png";
const std::string kSmallAsteroid01 = "../assets/gfx/asteroid-small-01.png";
const std::string kSmallAsteroid02 = "../assets/gfx/asteroid-small-02.png";
//checkpoint art
const std::string kCheckpoint = "../assets/gfx/checkpoint.png";
//player character art
const std::string KPlayerShip = "../assets/gfx/player-ship.png";
//competitior art
const std::string kComptetitor = "../assets/gfx/enemy-drone.png";
//On initialize scene method.
void MainGameScene::onInitializeScene()
{
	//load the font we want to use
	m_robotoFont.loadFromFile(kMainGameFont);
}

void MainGameScene:: onUpdate(double deltaTime)
{	
	captureInput();
	UpdateMyTimer(deltaTime);
	if(m_competetitor!=nullptr)
	{
		m_competetitor->MoveTowerds();
	}
}
void MainGameScene::onShowScene()
{
	//create the physics world
	Scene::createPhysicsWorld(sf::Vector2f(0.0f, 0.0f));
	LoadLevel(GameState::getInstance().selectedLevel);
	if(m_competetitor!=nullptr)
	{
		m_competetitor->AssignListOfCheckpoints(checkpoints);
	}
	m_timerText = std::make_shared<gbh::TextNode>("0",m_robotoFont,40);
	m_timerText->setOrigin(1, 1);
	m_timerText->setPosition(1270, 700);
	getOverlay().addChild(m_timerText);
	AdvanceCheckpoints();
	m_mainMusic.play();
}
void MainGameScene::onHideScene()
{
	m_mainMusic.stop();
	setDrawPhysicsDebug(false);
	removeAllChildren(true);
}
void MainGameScene::onKeyboardEvent(sf::Event& event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		ToggleDebugDraw();
	}
	m_MainCamera->ZoomCamera();
	EndGame();
}
void MainGameScene::onBeginPhysicsContact(const gbh::PhysicsContact& contact)
{
	//get the reference to the player character
	gbh::Node* player = m_player.get();
	gbh::Node* competitor = m_competetitor.get();
	if(contact.containsNode(player))
	{
		gbh::Node* otherNode = contact.otherNode(player);
		if(otherNode->getName()=="checkPoint")
		{
			AdvanceCheckpoints();
		}
	}
	else if(contact.containsNode(competitor))
	{
		gbh::Node* othernode = contact.otherNode(competitor);
		if(othernode->getName()== "checkPoint")
		{
			m_competetitor->FindNewCeckPoint();
		}
	}
	
}
//Here we advance what checkpoint we want to show
void MainGameScene::AdvanceCheckpoints()
{
	if(currentCheckPoint>=0&&currentCheckPoint<checkpoints.size())
	{
		checkpoints[currentCheckPoint]->MarkAsReached();
		CheckRaceCourseState();
		currentCheckPoint++;
	}
	else if(currentCheckPoint==-1)
	{
		currentCheckPoint = 0;
	}
	if(currentCheckPoint<checkpoints.size())
	{
		checkpoints[currentCheckPoint]->ToggleOnOff(true);
	}
	else
	{
		std::cout << "Congratulations you have finished the race";
	}
}
//This function goes through the checkpoint and check if they are active and increase a counter for each of them that is active.
//when the number of active checkpoints is equal to the number of checkpoints in the game
void MainGameScene::CheckRaceCourseState()
{
	int reachedCheckpoints = 0;
	for(int i = 0; i<checkpoints.size(); i++)
	{
		if (checkpoints[i]->GetActive())
		{
			reachedCheckpoints++;
		}
	}
	if(reachedCheckpoints==checkpoints.size())
	{
		m_courseFinished = true;
		HandleOverlay(true);
	}
}
void MainGameScene::captureInput() 
{	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))		
	{
		m_player->getPhysicsBody()->setLinearDamping(2.0);
		m_player->getPhysicsBody()->applyForceToCenter(m_player->forwardVector()*accelration);		
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{		
		m_player->getPhysicsBody()->setLinearDamping(m_player->getPhysicsBody()->getLinearDamping() + 0.1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{		
		m_player->rotate(-1);	

	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{		
		m_player->rotate(1);	
	}
	
}
// This functions toggles the debugdraw function active or inactive dependent on the state of a bool(getDrawPhysicsDebug) and will be triggered when the player
//press the U key.
void MainGameScene::ToggleDebugDraw()
{
	if(getDrawPhysicsDebug())
	{
		setDrawPhysicsDebug(false);
	}
	else if(!getDrawPhysicsDebug())
	{
		setDrawPhysicsDebug(true);
	}
}
//As the functions at the very bottom of this program becomes obsolete I introduce a function for loading levels from JSON files
//using the Nholman library
void MainGameScene::LoadLevel(const std::string& fileName)
{
	//declarations of the variables a ifstream file and a jsonFile
	std::ifstream file(fileName);
	nlohmann::json jsonFile;
	//try and catch statement
	try
	{
		jsonFile = nlohmann::json::parse(file);
	}
	catch(const std::exception& except)
	{
		std::cout << "Failed to load level from file " << fileName << ":" << except.what() << "\n";
	}
	//Loading functions for the levels, boundaries, backgrounds, checkpoints, asteroids and more are all loaded in via the below functions
	LoadBoundaries(jsonFile);
	LoadBackground(jsonFile);
	LoadMusic(jsonFile);
	LoadCeckpoints(jsonFile);
	LoadActors(jsonFile);
	LoadPlayer(jsonFile);
	LoadEnemySip(jsonFile);
	LoadCamera(jsonFile);
	
}

//loading functions needed by load level
void MainGameScene::LoadBoundaries(nlohmann::json& inJSon)
{
	nlohmann::json jsWorldBoundary = inJSon["WorldBoundaries"];
	float xSize = jsWorldBoundary["sizeX"].get<float>();
	float ySize = jsWorldBoundary["sizeY"].get<float>();
	float xPos = jsWorldBoundary["PlaceMentX"].get<float>();
	float yPos = jsWorldBoundary["placementY"].get<float>();

	std::shared_ptr<gbh::Node> m_boudnaries = std::make_shared<gbh::Node>();//node that will hold the boundaries for the world
	m_boudnaries->setName("boundaries");
	m_boudnaries->setPhysicsBody(getPhysicsWorld()->createEdgeBox(sf::Vector2(xSize, ySize)));
	m_boudnaries->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_boudnaries->setPosition(xPos, yPos);
	addChild(m_boudnaries);
}
void MainGameScene::LoadBackground(nlohmann::json& inJSon)
{
	nlohmann::json jsBackground = inJSon["BackgroundImage"];

	if (jsBackground != NULL)
	{
		const std::string backgroundImage = jsBackground["imagefile"].get<std::string>();
		float bgPosX = jsBackground["posX"].get<float>();
		float bgPosY = jsBackground["posY"].get<float>();
		std::shared_ptr<gbh::SpriteNode> m_background = std::make_shared<gbh::SpriteNode>(backgroundImage);
		m_background->setName("Background");
		m_background->setOrigin(0.5f, 0.5f);
		m_background->setPosition(bgPosX, bgPosY);
		addChild(m_background);
	}
	else if (jsBackground == NULL)
	{
		std::shared_ptr<gbh::SpriteNode> m_background = std::make_shared<gbh::SpriteNode>(kBackGround);
		m_background->setName("Background");
		m_background->setOrigin(0.5f, 0.5f);
		m_background->setPosition(260, -200);
		addChild(m_background);
	}
}
void MainGameScene::LoadMusic(nlohmann::json& inJSon)
{
	nlohmann::json jsMusic = inJSon["Music"];

	if (jsMusic != NULL)
	{
		const std::string music = jsMusic["path"].get< const std::string>();
		m_mainMusic.openFromFile(music);
	}
	else if (jsMusic == NULL)
	{
		m_mainMusic.openFromFile(kMainMusic);
	}
}
void MainGameScene::LoadCeckpoints(nlohmann::json& inJSon)
{
	nlohmann::json jsonCheckpoints = inJSon["checkpoints"];
	if (!jsonCheckpoints.is_array())
	{
		std::cout << "Level file either does not include a 'checkpoint' entry of it is not an array";
		return;
	}
	if (jsonCheckpoints.is_array())
	{
		for (int i = 0; i < jsonCheckpoints.size(); i++)
		{
			float x = jsonCheckpoints[i]["x"].get<float>();
			float y = jsonCheckpoints[i]["y"].get<float>();
			std::shared_ptr<CheckPoint> point = std::make_shared<CheckPoint>(kCheckpoint);
			point->setPhysicsBody(getPhysicsWorld()->createCircle(50));
			point->PlaceCeckpoint(sf::Vector2f(x, y));
			addChild(point);
			checkpoints.push_back(point);
		}
	}
}
void MainGameScene::LoadActors(nlohmann::json& inJSon)
{
	nlohmann::json objects = inJSon["Objects"];
	nlohmann::json jsActors = inJSon["Actors"];
	gbh::PhysicsMaterial asteroidMat;//create a physics material for the asteroids
	if (objects.is_object() && jsActors.is_array())
	{
		for (int i = 0; i < jsActors.size(); i++)
		{
			nlohmann::json asteroid = jsActors[i];
			nlohmann::json object = objects[asteroid["object"].get<std::string>()];

			if (object.is_object())
			{
				std::string imagepath = object["image"].get<std::string>();
				std::string type = object["Body"]["type"].get<std::string>();
				float size = object["Body"]["radius"].get<float>();
				float xpos = jsActors[i]["x"].get<float>();
				float ypos = jsActors[i]["y"].get<float>();
				bool randomVelocity = jsActors[i]["randomVelocity"].get<bool>();

				std::shared_ptr<Asteroid> ast = std::make_shared<Asteroid>(imagepath);
				if (type == "Big")
				{
					asteroidMat.density = 3000;
				}
				if (type == "Medium")
				{
					asteroidMat.density = 2000;
				}
				if (type == "Small")
				{
					asteroidMat.density = 1000;
				}
				ast->setPhysicsBody(getPhysicsWorld()->createCircle(size, asteroidMat));
				ast->SetUpAsteroid(sf::Vector2f(xpos, ypos));
				std::mt19937 randomSeed = std::mt19937(std::time(nullptr));
				std::uniform_int_distribution<int> velocity(-50,50);
				if(randomVelocity)
				{
					ast->getPhysicsBody()->setLinearVelocity(sf::Vector2f((float)velocity(randomSeed), (float)velocity(randomSeed)));
				}
				ast->getPhysicsBody()->setAngularVelocity((float)velocity(randomSeed));
				addChild(ast);	
			}


		}
	}
}
void MainGameScene::LoadPlayer(nlohmann::json& inJSon)
{
	nlohmann::json startPosition = inJSon["PlayerPosition"];
	float plX = startPosition["playerX"].get<float>();
	float plY = startPosition["playerY"].get<float>();

	m_player = std::make_shared<gbh::SpriteNode>(KPlayerShip);
	m_player->setName("Player");
	m_player->setOrigin(0.5, 0.5);
	m_player->setPosition(plX, plY);
	m_player->setScale(0.5, -0.5);
	m_player->rotate(180);
	//Physics for player ship added
	sf::Vector2f shipmainBody = sf::Vector2f(20.0f, 110.0f);
	sf::Vector2f shipSecondaryBody = sf::Vector2f(60, 15);
	gbh::PhysicsMaterial shipMaterial;
	shipMaterial.density = 3.0f;
	m_player->setPhysicsBody(getPhysicsWorld()->createEmptyBody());
	m_player->getPhysicsBody()->addBox(shipmainBody * 0.5f, sf::Vector2f(), shipMaterial);
	m_player->getPhysicsBody()->addBox(shipSecondaryBody * 0.5f, sf::Vector2f(0.0f, -5.0f), shipMaterial);
	m_player->getPhysicsBody()->setType(gbh::PhysicsBodyType::Dynamic);
	m_player->getPhysicsBody()->setLinearDamping(2.0f);
	m_player->getPhysicsBody()->setFixedRotation(true);
	addChild(m_player);
}
void MainGameScene::LoadEnemySip(nlohmann::json& inJSon)
{
	nlohmann::json enemyPosition = inJSon["OpponentPosition"];
	if(enemyPosition!= NULL)
	{
		float enemyPosX = enemyPosition["x"].get<float>();
		float enemyPosY = enemyPosition["y"].get<float>();

		m_competetitor = std::make_shared<AiControlledShip>(kComptetitor);
		m_competetitor->setOrigin(0.5, 0.5);
		m_competetitor->setPosition(enemyPosX, enemyPosY);
		m_competetitor->setScale(0.5, 0.5);

		gbh::PhysicsMaterial compMat;
		sf::Vector2f size = sf::Vector2f(60, 140);
		compMat.density = 3;
		m_competetitor->setPhysicsBody(getPhysicsWorld()->createEmptyBody());
		m_competetitor->getPhysicsBody()->addBox(size * 0.5f, sf::Vector2f(), compMat);
		m_competetitor->getPhysicsBody()->setType(gbh::PhysicsBodyType::Dynamic);
		m_competetitor->getPhysicsBody()->setLinearDamping(2.0f);
		m_competetitor->getPhysicsBody()->setFixedRotation(true);
		addChild(m_competetitor);
	}
}
void MainGameScene::LoadCamera(nlohmann::json& inJSon)
{
	nlohmann::json cameraVariable = inJSon["CameraVariable"];
	float camerastartX = cameraVariable["cameraX"].get<float>();
	float cameraStartY = cameraVariable["cameraY"].get<float>();
	float trackingX = cameraVariable["trackingX"].get<float>();
	float trackingY = cameraVariable["trackingY"].get<float>();

	m_MainCamera = std::make_shared<FollowCameraNode>();
	m_MainCamera->SetTarget(m_player);
	m_MainCamera->setPosition(camerastartX, cameraStartY);
	addChild(m_MainCamera);
	setCamera(m_MainCamera);
	m_MainCamera->SetTrackingArea(trackingX, trackingY);
	m_MainCamera->SetSpeed(2);
}

void MainGameScene::UpdateMyTimer(double deltaTime)
{
	if(!m_courseFinished)
	{
		m_playTime += deltaTime;
		char buffer[32];
		sprintf(buffer, "%.2f", m_playTime);
		m_timerText->setString(buffer);
	}
}
void MainGameScene::HandleOverlay(bool showOverlay)
{
	if(showOverlay)
	{
		std::shared_ptr<gbh::TextNode> instruction = std::make_shared<gbh::TextNode>("Press space to return to menue", m_robotoFont, 50);
		instruction->setName("PressSpace");
		instruction->setOrigin(0.5, 0.5);
		instruction->setPosition(500, 400);
		getOverlay().addChild(instruction);

		std::shared_ptr<gbh::TextNode> winText= std::make_shared<gbh::TextNode>("Course Finished", m_robotoFont, 80);
		winText->setName("YouWon");
		winText->setOrigin(0.5, 0.5);
		winText->setPosition(500, 200);
		getOverlay().addChild(winText);


		m_timerText->setPosition(500,600);
	}
	else if(!showOverlay)
	{
		getOverlay().removeAllChildren(true);
		m_timerText->setPosition(1270, 700);
	}
}
void MainGameScene::EndGame()
{
	if(m_courseFinished)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			currentCheckPoint = -1;
			m_playTime = 0;
			m_timerText->setString("0");
			m_courseFinished = false;
			checkpoints.clear();
			HandleOverlay(false);
			gbh::Game::getInstance().changeScene("title");
		}
	}
}


