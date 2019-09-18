#pragma once
#include "BaseEngine.h"
#include "CW4TileManager.h"
#include "JPGImage.h"
#include <string>
#include <vector>
using namespace std;
class CW4Engine :
	public BaseEngine
{
public:
	CW4Engine();
	~CW4Engine();
	void SetupBackgroundBuffer();



	CW4TileManager CW4_TM;
	ImageData bg;

	int InitialiseObjects();
	//CW4Spawn* SpawnOb = new CW4Spawn(this);
	//CW4ScoreBoard* ScoreBoardOb = new CW4ScoreBoard(this);
	void MouseDown(int iButton, int iX, int iY);
	int enemyKill = 0;
	int blood = 10;
	int bulletIndex = 8;
	int lastMag = 10;
	bool isShoot = true;
	bool isPause = false;
	int state = 0;
	char tempChar;
	char name[11];
	int countChar = 0;
	void KeyUp(int iKeyCode);
	void saveData();
	void loadData();
	string temp;
	vector<string> data;
};

