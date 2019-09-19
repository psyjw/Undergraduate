#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
class Trigger :
	public DisplayableObject,
	public Animation
{
public:
	Trigger();
	~Trigger();
	void Display();
	void Update(const double& deltaTime);

private:
	void curvedFront();
	void curvedLeft();
	void curvedBack();
	void curvedRight();
	void entity();
	bool half = false;
};

