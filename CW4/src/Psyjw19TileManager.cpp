#include "header.h"
#include "Psyjw19TileManager.h"



Psyjw19TileManager::Psyjw19TileManager()
	: TileManager(100, 100)
{
}


Psyjw19TileManager::~Psyjw19TileManager()
{
}

//windowWidth and windowHeight are number of pixels of the window
//startWidth and startHeight are the up-left coordinate; Next tow are the bottom-right coordiante
//GetColor can select a specific color according to the appointed integer value
void Psyjw19TileManager::DrawTileAt(BaseEngine* pEngine, SDL_Surface* pSurface, int windowWidth, int windowHeight, int startWidth, int startHeight) const
{
	pEngine->DrawRectangle(
		startWidth + 25,
		startHeight + 25,
		startWidth + 25 + GetTileWidth()/2,
		startHeight + 25 + GetTileHeight()/2,
		pEngine->GetColour(GetValue(windowWidth, windowHeight)),
		pSurface);
}
