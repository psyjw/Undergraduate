#pragma once
#include "TileManager.h"
class CW4TileManager :
	public TileManager
{
public:
	CW4TileManager();
	~CW4TileManager();
	void DrawTileAt(BaseEngine* pEngine, SDL_Surface* pSurface, int windowWidth, int windowHeight, int startWidth, int startHeight) const;
};

