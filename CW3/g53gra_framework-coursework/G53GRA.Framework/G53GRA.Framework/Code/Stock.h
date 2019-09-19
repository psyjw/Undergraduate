#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Stock :
	public DisplayableObject,
	public Animation
{
public:
	Stock();
	~Stock();
	void Display();
	void Update(const double& deltaTime);

private:
	string sequence = "f/+ff/+f/+f[+f]f/";
	float angle = 90.f;
	void branch(float h, float r);
	int substatus = 0;	//0 = assemble, 1 = disassemble
	GLint texID;
};

