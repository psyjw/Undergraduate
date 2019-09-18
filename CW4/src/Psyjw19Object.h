#pragma once
#include "DisplayableObject.h"
class Psyjw19Object :
	public DisplayableObject
{
public:
	Psyjw19Object(BaseEngine* pEngine);
	~Psyjw19Object();
	void Draw();
	void DoUpdate(int currentTime);
	void setPostion(int iX, int iY);
};

