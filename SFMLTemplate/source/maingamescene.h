#pragma once
#include "sfml-engine/scene.h"
#include <SFML/Audio.hpp>

class MainGameScene :public gbh::Scene 
{
protected:
	void onInitializeScene() override;

	virtual void onUpdate(double deltaTime);
private:
	sf::Font m_robotoFont;
	//physics related variables
	float accelration = 2000.0f;
	sf::Vector2f moveForce = sf::Vector2f(0.0f, 0.0f);
	
	//functions

	//I want to take the input via a separate function that I call from the update function
	void captureInput();
};