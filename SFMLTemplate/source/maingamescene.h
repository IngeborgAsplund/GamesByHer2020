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
private:
	sf::Font m_robotoFont;
	sf::Music m_mainMusic;
	//physics related variables
	float accelration = 2000.0f;
	sf::Vector2f moveForce = sf::Vector2f(0.0f, 0.0f);
	
	//functions

	//I want to take the input via a separate function that I call from the update function
	void captureInput();
};