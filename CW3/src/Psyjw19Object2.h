#pragma once
#include "DisplayableObject.h"
class Psyjw19Object2 :
	public DisplayableObject
{
public:
	Psyjw19Object2(BaseEngine* pEngine);
	~Psyjw19Object2();
	void DoUpdate(int currentTime);
	void Draw();
	int towardsX;
	int towardsY;
	int iColor;
};

