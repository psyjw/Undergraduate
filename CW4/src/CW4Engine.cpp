#include "header.h"
#include "templates.h"
#include "CW4Engine.h"
#include "TileManager.h"
#include "CW4Enemy.h"
#include "CW4ScoreBoard.h"
#include "CW4Spawn.h"
#include "CW4Player.h"
#include "CW4Bullet.h"
#include <fstream>
#include <iostream>



CW4Engine::CW4Engine()
{
}


CW4Engine::~CW4Engine(void)
{
}



void CW4Engine::SetupBackgroundBuffer()
{
	switch (state)
	{
	case 0:
		isPause = true;
		bg.LoadImage("start.png");
		bg.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, bg.GetWidth(), bg.GetHeight());
		DrawBackgroundString(400, 480, "Press Enter to Enter Your Name.", 0xFF0000, NULL);
		Redraw(true);
		break;
	case 1:
		//Tiles are 100x100, so there are 8 tiles on the width and 6 on the height
		CW4_TM.SetSize(16, 9);
		//Set all tiles' value to be 0
		for (int height = 0; height < 9; height++) {
			for (int width = 0; width < 16; width++) {
				if (height > 6) {
					CW4_TM.SetValue(width, height, 0);
				}
				else {
					CW4_TM.SetValue(width, height, 7);
				}
			}
		}

		//Draw all tiles on the background
		CW4_TM.DrawAllTiles(this, this->GetBackground(), 0, 0, 15, 8);

		bg.LoadImage("BG.jpg");
		bg.RenderImageWithMask(this->GetBackground(), 0, 0, ((CW4ScoreBoard*)GetDisplayableObject(1))->bgX, 0, bg.GetWidth(), bg.GetHeight());
		Redraw(true);
		break;
	case 2:
		bg.LoadImage("start.png");
		bg.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, bg.GetWidth(), bg.GetHeight());
		DrawBackgroundRectangle(500, 320, 780, 360, 0xFFFFFF);
		DrawBackgroundString(500, 320, name, 0x000000, NULL);
		DrawBackgroundString(400, 480, "Press Enter to Start the Game.", 0xFF0000, NULL);
		Redraw(true);
		break;
	case 3:
		DestroyOldObjects();
		bg.LoadImage("win.jpg");
		bg.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, bg.GetWidth(), bg.GetHeight());
		DrawBackgroundString(500, 320, "Congratulation, You Win! Press ESC to exit.", 0xFF0000, NULL);
		Redraw(true);
		break;
	case 4:
		DestroyOldObjects();
		bg.LoadImage("fail.jpg");
		bg.RenderImageWithMask(this->GetBackground(), 0, 0, 0, 0, bg.GetWidth(), bg.GetHeight());
		DrawBackgroundString(500, 320, "You Lose! Press ESC to exit.", 0xFF0000, NULL);
		Redraw(true);
		break;
	}
}


int CW4Engine::InitialiseObjects()
{
	if (state != 1) {
		return 0;
	}
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(16);
	StoreObjectInArray(0, new CW4Spawn(this));
	StoreObjectInArray(1, new CW4ScoreBoard(this));
	StoreObjectInArray(2, new CW4Player(this));
	StoreObjectInArray(3, new CW4Enemy(this, 0, 0, 0, false, 0));
	StoreObjectInArray(4, new CW4Enemy(this, 0, 0, 0, false, 0));
	StoreObjectInArray(5, new CW4Enemy(this, 0, 0, 0, false, 0));
	StoreObjectInArray(6, new CW4Enemy(this, 0, 0, 0, false, 0));
	StoreObjectInArray(7, new CW4Enemy(this, 0, 0, 0, false, 0));
	StoreObjectInArray(15, NULL);
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	/*StoreObjectInArray(0, psyjw19_Ob);
	StoreObjectInArray(1, psyjw19_Ob2);
	StoreObjectInArray(2, psyjw19_Text);
	StoreObjectInArray(3, NULL);*/
	return 0;
}


void CW4Engine::MouseDown(int iButton, int iX, int iY)
{
	if (lastMag == 0) {
		return;
	}
	if (isShoot == false) {
		return;
	}
	if (isPause == true) {
		return;
	}
	for (int i = 3; i < 8; i++) {
		if (GetDisplayableObject(i) != NULL && GetDisplayableObject(i)->IsVisible() == true) {
			if (((CW4Enemy*)GetDisplayableObject(i))->eliminate(iX, iY) == true) {
				((CW4Player*)GetDisplayableObject(2))->towards = 1;
				lastMag = lastMag - 1;
				isShoot = false;
				CW4Bullet* playerAttack = new CW4Bullet(this, 1, iX, iY, i);
				if (bulletIndex > 14) {
					bulletIndex = 8;
					StoreObjectInArray(bulletIndex, playerAttack);
				}
				else {
					StoreObjectInArray(bulletIndex, playerAttack);
				}
				bulletIndex = bulletIndex + 1;

				
				return;
			}
		}
	}
}



void CW4Engine::KeyUp(int iKeyCode)
{
	switch (state) 
	{
	case 0:
		if (iKeyCode == SDLK_RETURN) {
			state = 2;
			SetupBackgroundBuffer();
			Redraw(true);
		}
		break;
	case 1:
		if (iKeyCode == SDLK_SPACE) {
			if (isPause == false) {
				isPause = true;
			}
			else {
				isPause = false;
			}
		}
		else if (iKeyCode == SDLK_s) {
			saveData();
		}
		else if (iKeyCode == SDLK_l) {
			loadData();
		}
		break;
	case 2:
		if (iKeyCode == SDLK_RETURN) {
			state = 1;
			InitialiseObjects();
			SetupBackgroundBuffer();
			Redraw(true);	
			isPause = false;
		}
		else if (iKeyCode == SDLK_BACKSPACE) {
			if (countChar > 0) {
				countChar = countChar - 1;
				name[countChar] = ' ';
				SetupBackgroundBuffer();
				Redraw(true);
			}
		}
		else {
			if (countChar < 10) {
				tempChar = iKeyCode;
				name[countChar] = tempChar;
				countChar = countChar + 1;
				SetupBackgroundBuffer();
				Redraw(true);
			}
		}
		break;
	case 3:
		if (iKeyCode == SDLK_ESCAPE) {
			SetExitWithCode(0);
		}
		break;
	case 4:
		if (iKeyCode == SDLK_ESCAPE) {
			SetExitWithCode(0);
		}
		break;
	}
}


void CW4Engine::saveData()
{
	isPause = true;
	ofstream saveFile("Data.txt");
	saveFile << to_string(enemyKill) << " " << to_string(blood) << " " << to_string(bulletIndex) << " " << to_string(lastMag) << " " << (string)name << endl;
	saveFile << ((CW4Spawn*)GetDisplayableObject(0))->save() << endl;
	saveFile << ((CW4ScoreBoard*)GetDisplayableObject(1))->save() << endl;
	for (int i = 3; i < 8; i++) {
		saveFile << (((CW4Enemy*)GetDisplayableObject(i))->save()) << endl;
	}
	for (int j = 8; j < 15; j++) {
		if (GetDisplayableObject(j) == NULL) {
			break;
		}
		saveFile << (((CW4Bullet*)GetDisplayableObject(j))->save()) << endl;
	}
	saveFile.close();
}


void CW4Engine::loadData()
{
	isPause = true;
	int j = 10;
	ifstream openFile("Data.txt");
	/*if (!openFile.is_open()) {
		cout << "Error opening file!" << endl;
		exit(0);
	}*/
	while (!openFile.eof()) {
		openFile >> temp;
		data.push_back(temp);
	}
	int size = data.size();
	
	enemyKill = stoi(data[0]);
	blood = stoi(data[1]);
	bulletIndex = stoi(data[2]);
	lastMag = stoi(data[3]);
	(string)name = data[4];

	StoreObjectInArray(0, new CW4Spawn(this, stoi(data[5]), stoi(data[6]), stoi(data[7]), stoi(data[8])));
	StoreObjectInArray(1, new CW4ScoreBoard(this, stoi(data[9])));
	
	for (int i = 3; i < 8; i++) {
		if (stoi(data[j + 6]) == 0) {
			StoreObjectInArray(i, new CW4JetFighter(this, stoi(data[j]), stoi(data[j + 1]), stoi(data[j + 2]), stoi(data[j + 3]), stoi(data[j + 4]), stoi(data[j + 5]), stoi(data[j + 6]), stoi(data[j + 7])));
		}
		else if (stoi(data[j + 6]) == 1) {
			StoreObjectInArray(i, new CW4Soldier(this, stoi(data[j]), stoi(data[j + 1]), stoi(data[j + 2]), stoi(data[j + 3]), stoi(data[j + 4]), stoi(data[j + 5]), stoi(data[j + 6]), stoi(data[j + 7])));
		}
		else if (stoi(data[j + 6]) == 2) {
			StoreObjectInArray(i, new CW4Tank(this, stoi(data[j]), stoi(data[j + 1]), stoi(data[j + 2]), stoi(data[j + 3]), stoi(data[j + 4]), stoi(data[j + 5]), stoi(data[j + 6]), stoi(data[j + 7])));
		}
		j = j + 8;
		
	}

	for (int i = 8; i < 15; i++) {
		if (j >= size - 1) {
			for (i; i < 15; i++) {
				StoreObjectInArray(i, NULL);
			}
			break;
		}
		StoreObjectInArray(i, new CW4Bullet(this, stoi(data[j]), stoi(data[j+1]), stoi(data[j+2]), stoi(data[j+3]), stoi(data[j+4]), stoi(data[j+5]), stoi(data[j+6]), stoi(data[j+7])));
		j = j + 8;
	}

	

	openFile.close();
		/*StoreObjectInArray(0, new CW4Spawn(this, stoi((openFile>>temp)), stoi(openFile>>temp), stoi(), stoi(temp)));

		StoreObjectInArray(0, new CW4Spawn(this));
		StoreObjectInArray(1, new CW4ScoreBoard(this));
		StoreObjectInArray(2, new CW4Player(this));
		StoreObjectInArray(3, new CW4Enemy(this, 0, 0, 0, false, 0));
		StoreObjectInArray(4, new CW4Enemy(this, 0, 0, 0, false, 0));
		StoreObjectInArray(5, new CW4Enemy(this, 0, 0, 0, false, 0));
		StoreObjectInArray(6, new CW4Enemy(this, 0, 0, 0, false, 0));
		StoreObjectInArray(7, new CW4Enemy(this, 0, 0, 0, false, 0));*/
	
	
}
