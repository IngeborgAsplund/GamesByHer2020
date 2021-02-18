#pragma once
#include<string>
#include<vector>

#include"sfml-engine/scene.h"
#include"sfml-engine/spritenode.h"
#include"SFML/Audio/Music.hpp"
class LevelSelectScene:public gbh::Scene
{
protected:
	void onInitializeScene() override;
	virtual void onShowScene()override;
	virtual void onHideScene()override;
	virtual void onMouseEvent(sf::Event& event)override;
private:
	//variables
	sf::Music m_selectscreenMusic;
	std::vector<std::string>levels;//this contains the strings for the json
	std::vector<std::string>buttonGraphics;//this contains all the adresses to the buttons
	//functions
	void FillLists();//this method fills the lists with buttons and is called at scene initialization
	void CreateButtons();//this method creates all the buttons
};