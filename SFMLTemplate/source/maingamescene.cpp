//include headerfile for this scriptfile
#include"asteroid.h"
#include "gamestate.h"
#include"maingamescene.h"
//include of standard c++ libraries
#include<fstream>
#include<iostream>
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
//On initialize scene method.
void MainGameScene::onInitializeScene()
{
	//load the font we want to use
	m_robotoFont.loadFromFile(kMainGameFont);
}

void MainGameScene:: onUpdate(double deltaTime)
{	
	captureInput();
	RotateObstacles();
	UpdateMyTimer(deltaTime);
}
void MainGameScene::onShowScene()
{
	//create the physics world
	Scene::createPhysicsWorld(sf::Vector2f(0.0f, 0.0f));
	LoadLevel(GameState::getInstance().selectedLevel);
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
	if(contact.containsNode(player))
	{
		gbh::Node* otherNode = contact.otherNode(player);
		if(otherNode->getName()=="checkPoint")
		{
			AdvanceCheckpoints();
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
		m_player->getPhysicsBody()->setLinearDamping(3.0);
		m_player->getPhysicsBody()->applyForceToCenter(m_player->forwardVector()*accelration);
		/*moveForce.y  -= 1.0;*/
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{		
		/*moveForce.y += 1.0;*/
		m_player->getPhysicsBody()->setLinearDamping(m_player->getPhysicsBody()->getLinearDamping() + 0.1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{		
		m_player->rotate(-1);
		/*moveForce.x -= 1.0;*/		

	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{		
		m_player->rotate(1);	
		/*moveForce.x += 1.0;*/
	}
	/*moveForce = gbh::math::normalize(moveForce);
	player->getPhysicsBody()->applyForceToCenter(moveForce*accelration);*/
	
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
	//define what is found in json object
	//boundary
	nlohmann::json jsWorldBoundary = jsonFile["WorldBoundaries"];
	float xSize = jsWorldBoundary["sizeX"].get<float>();
	float ySize = jsWorldBoundary["sizeY"].get<float>();
	float xPos = jsWorldBoundary["PlaceMentX"].get<float>();
	float yPos = jsWorldBoundary["placementY"].get<float>();

	std::shared_ptr<gbh::Node> m_boudnaries = std::make_shared<gbh::Node>();//node that will hold the boundaries for the world
	m_boudnaries->setName("boundaries");
	m_boudnaries->setPhysicsBody(getPhysicsWorld()->createEdgeBox(sf::Vector2(xSize,ySize)));
	m_boudnaries->getPhysicsBody()->setType(gbh::PhysicsBodyType::Static);
	m_boudnaries->setPosition(xPos,yPos);
	addChild(m_boudnaries);
	//bg image
	nlohmann::json jsBackground = jsonFile["BackgroundImage"];

	if(jsBackground!=NULL)
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
	else if(jsBackground==NULL)
	{		
		std::shared_ptr<gbh::SpriteNode> m_background = std::make_shared<gbh::SpriteNode>(kBackGround);
		m_background->setName("Background");
		m_background->setOrigin(0.5f, 0.5f);
		m_background->setPosition(260,-200);
		addChild(m_background);
	}
	//music loading
	nlohmann::json jsMusic = jsonFile["Music"];

	if(jsMusic!=NULL)
	{
		const std::string music = jsMusic["path"].get< const std::string>();
		m_mainMusic.openFromFile(music);
	}
	else if(jsMusic==NULL)
	{
		m_mainMusic.openFromFile(kMainMusic);
	}

	nlohmann::json jsonCheckpoints = jsonFile["checkpoints"];
	if(!jsonCheckpoints.is_array())
	{
		std::cout << "Level file either does not include a 'checkpoint' entry of it is not an array";
		return;
	}
	if(jsonCheckpoints.is_array())
	{
		for(int i =0; i<jsonCheckpoints.size();i++)
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
	nlohmann::json objects = jsonFile["Objects"];
	nlohmann::json jsActors = jsonFile["Actors"];
	gbh::PhysicsMaterial asteroidMat;//create a physics material for the asteroids
	if(objects.is_object()&&jsActors.is_array())
	{
		for(int i = 0; i<jsActors.size();i++)
		{
			nlohmann::json asteroid = jsActors[i];
			nlohmann::json object = objects[asteroid["object"].get<std::string>()];

			if(object.is_object())
			{
				std::string imagepath = object["image"].get<std::string>();
				std::string type = object["Body"]["type"].get<std::string>();
				float size = object["Body"]["radius"].get<float>();
				float xpos = jsActors[i]["x"].get<float>();
				float ypos = jsActors[i]["y"].get<float>();

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
				addChild(ast);
				rotatingObstacles.push_back(ast);
			}

			
		}
	}
	nlohmann::json startPosition = jsonFile["PlayerPosition"];
	float plX = startPosition["playerX"].get<float>();
	float plY = startPosition["playerY"].get<float>();
	
	m_player = std::make_shared<gbh::SpriteNode>(KPlayerShip);
	m_player->setName("Player");
	m_player->setOrigin(0.5, 0.5);
	m_player->setPosition(plX, plY);
	m_player->setScale(0.5, -0.5);
	m_player->rotate(180);
	//Physics for player ship added
	sf::Vector2f shipsize = sf::Vector2f(55.0f, 102.0f);
	m_player->setPhysicsBody(getPhysicsWorld()->createBox(shipsize * 0.5f));
	m_player->getPhysicsBody()->setType(gbh::PhysicsBodyType::Dynamic);
	m_player->getPhysicsBody()->setLinearDamping(3.0f);
	m_player->getPhysicsBody()->setFixedRotation(true);
	addChild(m_player);

	nlohmann::json cameraVariable = jsonFile["CameraVariable"];
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
