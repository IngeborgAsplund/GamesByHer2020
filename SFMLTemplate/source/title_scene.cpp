#include "title_scene.h"

#include <iostream>

#include "sfml-engine/game.h"
#include "sfml-engine/shapenode.h"
#include "sfml-engine/spritenode.h"
#include "sfml-engine/textnode.h"

const std::string kTitleMusic = "../assets/music/titlescreen.ogg";
const std::string kTitleScreenFont = "../assets/fonts/roboto-regular.ttf";
const std::string kTitleScreenBackground = "../assets/gfx/starfield-01.png";
const std::string kPlayerShip = "../assets/gfx/player-ship.png";
const std::string kStartButton = "../assets/gfx/Startbutton.png";
const std::string kCreditsButton = "../assets/gfx/credits_button.png";
const std::string kTitleImage = "../assets/gfx/SpaceraceLogo.png";
const std::string krotatingAsteroid = "../assets/gfx/asteroid-medium-01.png";


void TitleScene::onInitializeScene()
{
	m_robotoFont.loadFromFile(kTitleScreenFont);
	m_titleMusic.openFromFile(kTitleMusic);
	m_titleMusic.setVolume(25);
	
	CreateBackground();
	CreateAsteroid();
	CreatePlayerShip();
	CreateUI();
}


void TitleScene::onUpdate(double deltaTime)
{
	RotateAsteroid();
}
//separate method rotating the asteroid in the title screen, I do not want the rotation to happen very quicly so I set the value
// very low as I want the rotating asteroid to be a subtle element that behaves in a slightly more realistic way.(than when it spins a lot as done with a high value)
void TitleScene::RotateAsteroid()
{
	std::shared_ptr<gbh::Node> asteroid = getFirstChildWithName("TitleScreenDeco",false);
	const float rotateDegree = 0.45f;
	asteroid->rotate(rotateDegree);
}
void TitleScene::onMouseEvent(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		std::shared_ptr<gbh::Node> node = this->getNodeAtViewPoint((float)event.mouseButton.x, (float)event.mouseButton.y);

		if (node)
		{
			//check if the node we clicked on is the startbutton and in that case start the main game.
			if(node->getName()=="StartButton")
			{
				gbh::Game::getInstance().changeScene("levelSelection");
			}
			if (node->getName() == "Credits")
			{
				gbh::Game::getInstance().changeScene("credits");
			}
		}
		
	}
}
void TitleScene::onShowScene()
{
	m_titleMusic.play();
}
void TitleScene::onHideScene()
{
	m_titleMusic.stop();
}
void TitleScene::CreateBackground()
{
	std::shared_ptr<gbh::SpriteNode> spriteNode = std::make_shared<gbh::SpriteNode>(kTitleScreenBackground);
	spriteNode->setName("Background");
	spriteNode->setPosition(640, 300);
	spriteNode->setOrigin(0.5f, 0.5f);
	addChild(spriteNode);
}
void TitleScene::CreateAsteroid()
{
	std::shared_ptr<gbh::SpriteNode> rotatingAsteroid = std::make_shared<gbh::SpriteNode>(krotatingAsteroid);
	rotatingAsteroid->setName("TitleScreenDeco");
	rotatingAsteroid->setPosition(150, 100);
	rotatingAsteroid->setOrigin(0.5f, 0.5f);
	addChild(rotatingAsteroid);
}
void TitleScene::CreatePlayerShip()
{
	std::shared_ptr<gbh::SpriteNode> ship = std::make_shared<gbh::SpriteNode>(kPlayerShip);
	ship->setPosition(620, 300);
	addChild(ship);
}
void TitleScene::CreateUI()
{
	std::shared_ptr<gbh::SpriteNode> title = std::make_shared<gbh::SpriteNode>(kTitleImage);
	title->setOrigin(0.5f, 0.5f);
	title->setPosition(640, 100);
	title->setName("Title");
	addChild(title);

	std::shared_ptr<gbh::SpriteNode> startButton = std::make_shared<gbh::SpriteNode>(kStartButton);
	startButton->setPosition(640, 560);
	startButton->setOrigin(0.5f, 0.5f);
	startButton->setName("StartButton");
	addChild(startButton);

	std::shared_ptr<gbh::SpriteNode>creditsButton = std::make_shared<gbh::SpriteNode>(kCreditsButton);
	creditsButton->setPosition(640, 460);
	creditsButton->setOrigin(0.5f, 0.5f);
	creditsButton->setName("Credits");
	addChild(creditsButton);
}
