#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Shell :
	public DisplayableObject,
	public Animation
{
public:
	Shell();
	~Shell();
	void Display();
	void Update(const double& deltaTime);

private:
	string sequence = "[+f]>| ";
	float angle = 90.f;
	void branch();
	bool half = false;
	GLint texID;
};

