
#include "TileManager.h"
class Psyjw19TileManager :
	public TileManager
{
public:
	Psyjw19TileManager();
	~Psyjw19TileManager();
	void DrawTileAt(BaseEngine* pEngine, SDL_Surface* pSurface, int windowWidth, int windowHeight, int startWidth, int startHeight) const;
};
