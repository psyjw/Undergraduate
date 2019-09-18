#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
#include "CW4Engine.h"
#include <string>
class CW4Bullet :
	public DisplayableObject
{
public:
	CW4Bullet(CW4Engine* pEngine, int type, int iX, int iY, int targetIndex);
	CW4Bullet(CW4Engine* pEngine, int iX, int iY, int type, int Distancex, int Distancey, int targetIndex, int Destineyy, bool visible);
	~CW4Bullet();
	ImageData bullet[2];
	int bullettype;
	void Draw();
	void DoUpdate(int iCurrentTime);
	int distanceX = 0;
	int distanceY = 0;
	int target;
	int destineyY = 0;
	int i = 20;
	int explosionTime = 0;
	CW4Engine* engine;
	std::string save();
};

