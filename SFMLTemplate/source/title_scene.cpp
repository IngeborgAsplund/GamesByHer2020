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
const std::string kTitleImage = "../assets/gfx/SpaceraceLogo.png";


void TitleScene::onInitializeScene()
{
	m_robotoFont.loadFromFile(kTitleScreenFont);
	m_titleMusic.openFromFile(kTitleMusic);
	m_titleMusic.setVolume(25);
	
	std::shared_ptr<gbh::SpriteNode> spriteNode = std::make_shared<gbh::SpriteNode>(kTitleScreenBackground);
	spriteNode->setName("Background");
	spriteNode->setPosition(640, 300);
	spriteNode->setOrigin(0.5f, 0.5f);
	addChild(spriteNode);

	std::shared_ptr<gbh::SpriteNode> title = std::make_shared<gbh::SpriteNode>(kTitleImage);
    title->setOrigin(0.5f, 0.5f);
	title->setPosition(640, 100);
	title->setName("Title");
	addChild(title);

	std::shared_ptr<gbh::SpriteNode> ship = std::make_shared<gbh::SpriteNode>(kPlayerShip);
	ship->setPosition(620, 300);
	addChild(ship);

	std::shared_ptr<gbh::SpriteNode> startButton = std::make_shared<gbh::SpriteNode>(kStartButton);
	startButton->setPosition(640, 560);
    startButton->setOrigin(0.5f, 0.5f);
	startButton->setName("StartButton");
	addChild(startButton);
}


void TitleScene::onUpdate(double deltaTime)
{
    std::shared_ptr<gbh::Node> titleNode = getFirstChildWithName("Title", false);
    
    //if (titleNode)
    //{
    //    titleNode->move(0, 50.f * (float)deltaTime);//moves title of the game downward, why?
    //}
}


void TitleScene::onMouseEvent(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		std::shared_ptr<gbh::Node> node = this->getNodeAtViewPoint((float)event.mouseButton.x, (float)event.mouseButton.y);

		if (node)
		{
			/*std::cout << "Clicked On: " << node->getName() << "\n";*/
			if(node->getName()=="StartButton")
			{
				gbh::Game::getInstance().changeScene("maingame");
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
