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
	CreateBackground();
	CreateCreditsContent();
	CreateButton();	
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
void CreditsScene::CreateBackground()
{
	std::shared_ptr<gbh::SpriteNode> starfield = std::make_shared<gbh::SpriteNode>(kCreditsBackground);
	starfield->setPosition(640, 300);
	starfield->setOrigin(0.5f, 0.5f);
	starfield->setName("Background");
	addChild(starfield);
}
void CreditsScene::CreateCreditsContent()
{
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

	std::shared_ptr<gbh::TextNode> creditsContent02 = std::make_shared<gbh::TextNode>("External Resources", m_RobotoFont, 30);
	creditsContent02->setPosition(640, 290);
	creditsContent02->setOrigin(0.5f, 0.5f);
	creditsContent02->setName("External resources");
	addChild(creditsContent02);
	
	std::shared_ptr<gbh::TextNode>creditscontent03 = std::make_shared<gbh::TextNode>("SFML engine code library by Microsoft",m_RobotoFont,25);
	creditscontent03->setPosition(640, 340);
	creditscontent03->setOrigin(0.5f, 0.5f);
	creditscontent03->setName("sfml ref");
	addChild(creditscontent03);

	std::shared_ptr<gbh::TextNode>creditscontent04 = std::make_shared<gbh::TextNode>("Box 2D physics engine by Erin Catto", m_RobotoFont, 25);
	creditscontent04->setPosition(640, 390);
	creditscontent04->setOrigin(0.5f, 0.5f);
	creditscontent04->setName("Box 2d");
	addChild(creditscontent04);

	std::shared_ptr<gbh::TextNode>creditscontent05 = std::make_shared<gbh::TextNode>("Nlohman Json by Niels Lohman", m_RobotoFont, 25);
	creditscontent05->setPosition(640, 440);
	creditscontent05->setOrigin(0.5f, 0.5f);
	creditscontent05->setName("NLohman Json");
	addChild(creditscontent05);

}
void CreditsScene::CreateButton()
{
	std::shared_ptr<gbh::SpriteNode> returnToMainButton = std::make_shared<gbh::SpriteNode>(kReturnToMenueButton);
	returnToMainButton->setOrigin(0.5f, 0.5f);
	returnToMainButton->setPosition(640, 560);
	returnToMainButton->setName("BackToMain");
	addChild(returnToMainButton);
}