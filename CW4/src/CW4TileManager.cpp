#include "header.h"
#include "CW4TileManager.h"



CW4TileManager::CW4TileManager()
	: TileManager(80, 80)
{
}


CW4TileManager::~CW4TileManager()
{
}




void CW4TileManager::DrawTileAt(BaseEngine* pEngine, SDL_Surface* pSurface, int windowWidth, int windowHeight, int startWidth, int startHeight) const
{
	pEngine->DrawRectangle(
		startWidth,
		startHeight,
		startWidth + GetTileWidth(),
		startHeight + GetTileHeight(),
		pEngine->GetColour(GetValue(windowWidth, windowHeight)),
		pSurface);
}
