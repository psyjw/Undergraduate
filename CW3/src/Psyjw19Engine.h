#pragma once
#include "BaseEngine.h"
#include "Psyjw19TileManager.h"
#include "Psyjw19Object.h"
#include "Psyjw19Object2.h"
#include "Psyjw19Text.h"
class Psyjw19Engine :
	public BaseEngine
{
public:
	Psyjw19Engine();
	~Psyjw19Engine();
	void SetupBackgroundBuffer();
private:
	Psyjw19TileManager psyjw19_TM;
	Psyjw19Object* psyjw19_Ob = new Psyjw19Object(this);
	Psyjw19Object2* psyjw19_Ob2 = new Psyjw19Object2(this);
	Psyjw19Text* psyjw19_Text = new Psyjw19Text(this);
public:
	int InitialiseObjects();
	void MouseDown(int iButton, int iX, int iY);
};


