#pragma once
#include "sfml-engine/scene.h"
#include <SFML/Audio.hpp>

class CreditsScene:public gbh::Scene
{
protected:
	void onInitializeScene() override;

	virtual void onMouseEvent(sf::Event& event);
	virtual void onShowScene();
	virtual void onHideScene();
private:
	sf::Font m_RobotoFont;
	sf::Music m_CreditsMusic;
};