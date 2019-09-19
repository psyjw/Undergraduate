#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Suppressor :
	public DisplayableObject,
	public Animation
{
public:
	Suppressor();
	~Suppressor();
	void Display();
	void Update(const double& deltaTime);

private:
	string sequence = "[>|][>/][+f]^[<|][</]";
	float angle = 90.f;
	int substatus = 0;	//0 = assemble, 1 = disassemble
	void branch();
	GLint texID;
};
