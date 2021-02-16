#pragma once
#include "checkpoint.h"
#include "followcameranode.h"
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
	void onBeginPhysicsContact(const gbh::PhysicsContact& contact)override;
private:
	sf::Font m_robotoFont;
	sf::Music m_mainMusic;
	//physics related variables
	float accelration = 2000.0f;
	sf::Vector2f moveForce = sf::Vector2f(0.0f, 0.0f);	
	std::vector<std::shared_ptr<gbh::Node>> rotatingObstacles;
	std::shared_ptr<FollowCameraNode> m_MainCamera;
	std::shared_ptr<gbh::SpriteNode> m_player;
	//checkpoint related variables
	int currentCheckPoint = -1;
	std::vector<std::shared_ptr<CheckPoint>> checkpoints;
	//time tracking variables
	double m_playTime = 0;
	std::shared_ptr<gbh::TextNode> m_timerText;	
	bool m_courseFinished = false;
	//functions
	void captureInput();
	void RotateObstacles();
	void ToggleDebugDraw();
	void LoadLevel(const std::string& fileName);
	void AdvanceCheckpoints();
	void CheckRaceCourseState();//function that count the number of activated checkpoints and
	void UpdateMyTimer(double deltaTime);
	void HandleOverlay(bool showOverlay);
	void EndGame();//when we have reached all of the checkpoints we can press space to return to the title scene

};