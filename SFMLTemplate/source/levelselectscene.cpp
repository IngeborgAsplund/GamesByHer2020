#include<iostream>
#include"sfml-engine/game.h"
#include "sfml-engine/spritenode.h"
#include"maingamescene.h"
#include"gamestate.h";
#include"levelselectscene.h"
const std::string kSelectionMusic = "../assets/music/titlescreen.ogg";
const std::string kSelectionScreenBackground = "../assets/gfx/starfield-01.png";
//buttons
const std::string kLevel1Button = "../assets/gfx/Level1_Button.png";
const std::string kLevel2Button = "../assets/gfx/Level2_Button.png";
void LevelSelectScene::onInitializeScene()
{
	m_selectscreenMusic.openFromFile(kSelectionMusic);
	FillLists();

	std::shared_ptr<gbh::SpriteNode> background = std::make_shared<gbh::SpriteNode>(kSelectionScreenBackground);
	background->setName("Bg");
	background->setPosition(900, 800);
	addChild(background);	

}
void LevelSelectScene::onShowScene()
{
	m_selectscreenMusic.play();
	CreateButtons();
}
void LevelSelectScene::onHideScene()
{
	m_selectscreenMusic.stop();
}
///Logic for determining which of the levels we wished to load
void LevelSelectScene::onMouseEvent(sf::Event& event)
{
	std::shared_ptr<gbh::Node> node = this->getNodeAtViewPoint((float)event.mouseButton.x, (float)event.mouseButton.y);
	
	if(node)
	{
		if(node->getName().length()>4)
		{
			if(node->getName().substr(0,2)=="->")
			{
				std::string level = node->getName().substr(2);
				GameState::getInstance().selectedLevel = level;
				gbh::Game::getInstance().changeScene("maingame");
			}
		}
	}
}
void LevelSelectScene::FillLists()
{
	levels.push_back("../assets/Levels/level1.json");
	levels.push_back("../assets/Levels/level2.json");

	buttonGraphics.push_back("../assets/gfx/Level1_Button.png");
	buttonGraphics.push_back("../assets/gfx/Level2_Button.png");
}
void LevelSelectScene::CreateButtons()
{
	for(int i = 0; i<levels.size();i++)
	{
		std::shared_ptr<gbh::SpriteNode> button = std::make_shared<gbh::SpriteNode>(buttonGraphics[i]);
		button->setName("->" + levels[i]);
		button->setPosition(640.0f, 240 + 80 * i);
		addChild(button);
	}
}
