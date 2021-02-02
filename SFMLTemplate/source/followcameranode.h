#pragma once
#include"sfml-engine/cameranode.h"

//The follow camera node class inherits from the sfml engine default camera node it contains 
class FollowCameraNode: public gbh::CameraNode
{
protected:
	virtual void onUpdate(double deltaTime)override;
public:
	void SetTarget(std::shared_ptr<gbh::Node> inTarget);
private:
	//variables
	std::shared_ptr<gbh::Node> target;//reference to what we want to target
	//methods
	void CheckCameraPlayerRelation(double deltaTime);
};