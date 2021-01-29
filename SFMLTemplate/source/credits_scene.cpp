#include"credits_scene.h"
//include of standard c++ libraries
#include<iostream>
//engine specific includes.
#include"sfml-engine/game.h"
#include"sfml-engine/shapenode.h"
#include"sfml-engine/spritenode.h"
#include"sfml-engine/textnode.h"

const std::string kCreditsMusic = "../assets/music/titlescreen.ogg";
const std::string kCreditsFont = "../assets/fonts/roboto-regular.ttf";
const std::string kCreditsBackground = "../assets/gfx/starfield-01.png";
const std::string kReturnToMenueButton = "../assets/gfx/Back-to-main-button.png";
//credits initializscene
void CreditsScene::onInitializeScene()
{
	//variable setup
	m_RobotoFont.loadFromFile(kCreditsFont);
	m_CreditsMusic.openFromFile(kCreditsMusic);
	//scene setup
	std::shared_ptr<gbh::SpriteNode> starfield = std::make_shared<gbh::SpriteNode>(kCreditsBackground);
	starfield->setPosition(640, 300);
	starfield->setOrigin(0.5f, 0.5f);
	starfield->setName("Background");
	addChild(starfield);

	std::shared_ptr<gbh::TextNode> creditsTitle = std::make_shared<gbh::TextNode>("Credits", m_RobotoFont, 50.);
	creditsTitle->setPosition(640, 100);
	creditsTitle->setOrigin(0.5f, 0.5f);
	creditsTitle->setName("Title");
	addChild(creditsTitle);
	
	std::shared_ptr<gbh::TextNode> creditsContent01 = std::make_shared<gbh::TextNode>("A game made by Ingeborg Asplund", m_RobotoFont, 30);
	creditsContent01->setPosition(640, 200);
	creditsContent01->setOrigin(0.5f, 0.5f);
	creditsContent01->setName("myCredit");
	addChild(creditsContent01);

	std::shared_ptr<gbh::TextNode> creditsContent02 = std::make_shared<gbh::TextNode>("Powered SFML Engine by Mircrosoft", m_RobotoFont, 30);
	creditsContent02->setPosition(640, 250);
	creditsContent02->setOrigin(0.5f, 0.5f);
	creditsContent02->setName("sfml reference");
	addChild(creditsContent02);

	std::shared_ptr<gbh::SpriteNode> returnToMainButton = std::make_shared<gbh::SpriteNode>(kReturnToMenueButton);
	returnToMainButton->setOrigin(0.5f, 0.5f);
	returnToMainButton->setPosition(640, 560);
	returnToMainButton->setName("BackToMain");
	addChild(returnToMainButton);
}
void CreditsScene::onMouseEvent(sf::Event& event)
{
	if(event.type == sf::Event::MouseButtonPressed)
	{
		std::shared_ptr<gbh::Node> pointerFound = this->getNodeAtViewPoint((float)event.mouseButton.x, (float)event.mouseButton.y);
		if(pointerFound)
		{
			if(pointerFound->getName()=="BackToMain")
			{
				gbh::Game::getInstance().changeScene("title");
			}
		}
	}
}
//Here we toggle credits music(right now the same as title)
void CreditsScene::onShowScene()
{
	m_CreditsMusic.play();
}
//here we toggle of credits music(right now the same as title)
void CreditsScene::onHideScene()
{
	m_CreditsMusic.stop();
}