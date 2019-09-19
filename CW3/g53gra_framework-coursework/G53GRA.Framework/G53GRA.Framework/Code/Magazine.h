#pragma once
#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Magazine :
	public DisplayableObject,
	public Animation
{
public:
	Magazine();
	~Magazine();
	void Display();
	void Update(const double& deltaTime);

private:
	void curvedFront();
	void curvedBack();
	void curvedLeft();
	void curvedRight();
	void entity();
	int substatus = 0;	//0 = assemble, 1 = disassemble
	GLint texID1, texID2, texID3;
};

