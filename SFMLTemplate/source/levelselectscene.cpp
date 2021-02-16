#include<iostream>
#include"sfml-engine/game.h"
#include "sfml-engine/spritenode.h"
#include"maingamescene.h"
#include"levelselectscene.h"
const std::string kSelectionMusic = "../assets/music/titlescreen.ogg";
const std::string kSelectionScreenBackground = "../assets/gfx/starfield-01.png";
//buttons
const std::string kLevel1Button = "../assets/gfx/Level1_Button.png";
const std::string kLevel2Button = "../assets/gfx/Level2_Button.png";
void LevelSelectScene::onInitializeScene()
{
	m_selectscreenMusic.openFromFile(kSelectionMusic);
	std::shared_ptr<gbh::SpriteNode> background = std::make_shared<gbh::SpriteNode>(kSelectionScreenBackground);
	background->setName("Bg");
	background->setPosition(900, 800);
	addChild(background);

	std::shared_ptr<gbh::SpriteNode>level1= std::make_shared<gbh::SpriteNode>(kLevel1Button);
	level1->setName("level1_Button");
	level1->setOrigin(0.5, 0.5);
	level1->setPosition(300,100);
	addChild(level1);

	std::shared_ptr<gbh::SpriteNode> level2 = std::make_shared<gbh::SpriteNode>(kLevel2Button);
	level2->setName("level2_Button");
	level2->setOrigin(0.5, 0.5);
	level2->setPosition(300,200);
	addChild(level2);
}
void LevelSelectScene::onShowScene()
{
	m_selectscreenMusic.play();
}
void LevelSelectScene::onHideScene()
{
	m_selectscreenMusic.stop();
}
///Logic for determining which of the levels we wished to load
void LevelSelectScene::onMouseEvent(sf::Event& event)
{
	std::shared_ptr<gbh::Node> hit = this->getNodeAtViewPoint((float)event.mouseButton.x, (float)event.mouseButton.y);
	
	if(hit)
	{
		if (hit->getName() == "level1_Button")
		{
			gbh::Game::getInstance().gLevel = "../assets/Levels/level1.json";
			gbh::Game::getInstance().changeScene("maingame");
		}
		if(hit->getName()=="level2_Button")
		{
			gbh::Game::getInstance().gLevel = "../assets/Levels/level2.json";
			gbh::Game::getInstance().changeScene("maingame");
		}
	}
}
