#pragma once
#include "DisplayableObject.h"

class Psyjw19Text :
	public DisplayableObject
{
public:
	Psyjw19Text(BaseEngine* pEngine);
	~Psyjw19Text();
	void Draw();
	void DoUpdate(int currentTime);
	char* text = (char*)malloc(7);
};

