#pragma once
#include"sfml-engine/cameranode.h"

//The follow camera node class inherits from the sfml engine default camera node it contains 
class FollowCameraNode: public gbh::CameraNode
{
protected:
	virtual void onUpdate(double deltaTime)override;
public:
	void SetTarget(std::shared_ptr<gbh::Node> inTarget);
	void SetTrackingArea(float xLimit, float yLimit);
	void SetSpeed(float speedMultiplier);
	void ZoomCamera();//zoom function for camera
private:
	//variables
	std::shared_ptr<gbh::Node> target;//reference to what we want to target
	float xLimit = 0;//xlimit is initilized as zero
	float yLimit = 0;//yLimit is initialized as zero
	float speedMultiplier = 0;//speedmultiplier initialized as zero
	//methods
	void CheckCameraPlayerRelation(double deltaTime);
};