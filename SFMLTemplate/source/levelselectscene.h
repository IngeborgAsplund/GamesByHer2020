#pragma once
#include"sfml-engine/scene.h"
#include"SFML/Audio/Music.hpp"
class LevelSelectScene:public gbh::Scene
{
protected:
	void onInitializeScene() override;
	virtual void onShowScene()override;
	virtual void onHideScene()override;
	virtual void onMouseEvent(sf::Event& event)override;
private:
	sf::Music m_selectscreenMusic;
};