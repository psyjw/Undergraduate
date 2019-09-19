#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Scope :
	public DisplayableObject,
	public Animation
{
public:
	Scope();
	~Scope();
	void Display();
	void Update(const double& deltaTime);

private:
	int substatus = 0;	//0 = assemble, 1 = disassemble
	GLint texID;

	void front();
	void top();
	void back();
	void bottom();
	void left();
	void right();
	void glass();
};

