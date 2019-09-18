#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
#include "CW4Engine.h"
class CW4Player :
	public DisplayableObject
{
public:
	CW4Player(CW4Engine* pEngine);
	~CW4Player();
	ImageData player[2];
	void Draw();
	int towards = 0;
	int fireTime = 200;
	int lifeTime = 300;
	int preTime = 0;
	int preLife = 100;
	void DoUpdate(int iCurrentTime);
};

