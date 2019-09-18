#include "header.h"
#include "templates.h"
#include "Psyjw19Engine.h"
#include "TileManager.h"



Psyjw19Engine::Psyjw19Engine()
{
}


Psyjw19Engine::~Psyjw19Engine()
{
}

void Psyjw19Engine::SetupBackgroundBuffer()
{
	//Tiles are 100x100, so there are 8 tiles on the width and 6 on the height
	psyjw19_TM.SetSize(8, 6);
	//Set all tiles' value to be 0
	for (int height = 0; height < 6; height++) {
		for (int width = 0; width < 8; width++) {
			psyjw19_TM.SetValue(width, height, 0);
		}
	}
	
	//Draw rectangles with 7 different colors one by one and in reverse
	for (int row = 0; row < GetWindowHeight(); row = row + 100) {
		for (int col = 0; col < GetWindowWidth(); col = col + 100) {
			if ((row % 200) == 0) {
				switch (col)
				{
				case 0: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFF0000); break;
				case 100: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFFA500); break;
				case 200: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFFFF00); break;
				case 300: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x008000); break;
				case 400: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x00FFFF); break;
				case 500: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x0000FF); break;
				case 600: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x800080); break;
				case 700: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFFFFFF); break;
				}	
			}
			else {
				switch (col)
				{
				case 0: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFFFFFF); break;
				case 100: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x800080); break;
				case 200: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x0000FF); break;
				case 300: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x00FFFF); break;
				case 400: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0x008000); break;
				case 500: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFFFF00); break;
				case 600: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFFA500); break;
				case 700: DrawBackgroundRectangle(col, row, col + 99, row + 99, 0xFF0000); break;
				}
			}
		}	
	}
	
	//Draw all tiles on the background
	psyjw19_TM.DrawAllTiles(this, this->GetBackground(), 0, 0, 7, 5);
	DrawBackgroundString(270, 30, "Background Text", 0xFFFFFF, NULL);
}


int Psyjw19Engine::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(4);
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	StoreObjectInArray(0, psyjw19_Ob);
	StoreObjectInArray(1, psyjw19_Ob2);
	StoreObjectInArray(2, psyjw19_Text);
	StoreObjectInArray(3, NULL);
	return 0;
}


void Psyjw19Engine::MouseDown(int iButton, int iX, int iY)
{
	psyjw19_Ob->setPostion(iX, iY);
}
