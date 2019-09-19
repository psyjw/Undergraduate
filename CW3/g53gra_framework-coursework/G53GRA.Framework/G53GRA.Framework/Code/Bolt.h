#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
class Bolt :
	public DisplayableObject,
	public Animation
{
public:
	Bolt();
	Bolt(GLint bodyID);
	~Bolt();
	void Display();
	void Update(const double& deltaTime);

private:
	bool half = false;
	GLint texID;
};

