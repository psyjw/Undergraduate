#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Bullet :
	public DisplayableObject,
	public Animation
{
public:
	Bullet();
	~Bullet();
	void Display();
	void Update(const double& deltaTime);

private:
	string sequence = "[+f^|]>|";
	float angle = 90.f;
	void branch();
	GLint texID;
};

