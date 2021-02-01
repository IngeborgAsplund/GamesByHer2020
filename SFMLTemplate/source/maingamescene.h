#pragma once
#include "sfml-engine/scene.h"
#include <SFML/Audio.hpp>

class MainGameScene :public gbh::Scene 
{
protected:
	void onInitializeScene() override;

	virtual void onUpdate(double deltaTime);
	//the below functions are used by the game when we want to start soemthing as soon as we enter this scene
	virtual void onShowScene();
	virtual void onHideScene();
	virtual void onKeyboardEvent(sf::Event & event)override;
private:
	sf::Font m_robotoFont;
	sf::Music m_mainMusic;
	//physics related variables
	float accelration = 2000.0f;
	sf::Vector2f moveForce = sf::Vector2f(0.0f, 0.0f);	
	std::vector<std::shared_ptr<gbh::Node>> rotatingObstacles;
	//functions
	void captureInput();
	void RotateObstacles();
	void ToggleDebugDraw();
};