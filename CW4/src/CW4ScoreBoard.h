#pragma once
#include "DisplayableObject.h"
#include "CW4Engine.h"
#include <string>
class CW4ScoreBoard :
	public DisplayableObject
{
public:
	CW4ScoreBoard(CW4Engine* pEngine);
	CW4ScoreBoard(CW4Engine* pEngine, int Bgx);
	~CW4ScoreBoard();
	void Draw();
	std::string score;
	std::string life;
	std::string magazine;
	void DoUpdate(int iCurrentTime);
	CW4Engine* engine;
	int bgX = -1280;
	string save();
};

