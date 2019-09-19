#pragma once
#include "DisplayableObject.h"
class Skybox :
	public DisplayableObject
{
public:
	Skybox();
	~Skybox();
	void Display();

private:
	GLint texID;
};

