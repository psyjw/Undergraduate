#include "header.h"
#include "templates.h"
#include "CW4Player.h"


CW4Player::CW4Player(CW4Engine* pEngine) :DisplayableObject(pEngine)
{
	m_iCurrentScreenX = m_iPreviousScreenX = 640;
	m_iCurrentScreenY = m_iPreviousScreenY = 560;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 0;
	m_iDrawHeight = 0;

	player[0].LoadImage("player.png");
	player[1].LoadImage("playerfire.png");
	// And make it visible
	SetVisible(true);
}


CW4Player::~CW4Player()
{
}


void CW4Player::Draw()
{
	player[towards].RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX - player[towards].GetWidth()/2, m_iCurrentScreenY - player[towards].GetHeight(), player[towards].GetWidth(), player[towards].GetHeight());
	GetEngine()->Redraw(true);
}


void CW4Player::DoUpdate(int iCurrentTime)
{
	if (((CW4Engine*)GetEngine())->isPause == true) {
		preTime = iCurrentTime;
		return;
	}
	if (GetEngine()->IsKeyPressed(SDLK_r)) {
		((CW4Engine*)GetEngine())->lastMag = 10;
	}
	if (towards == 1) {
		fireTime = fireTime - (iCurrentTime - preTime);
		if (fireTime <= 0) {
			towards = 0;
			fireTime = 200;
		}
	}
	if (preLife != ((CW4Engine*)GetEngine())->blood) {
		lifeTime = lifeTime - (iCurrentTime - preTime);
		if (lifeTime <= 0) {
			((CW4Engine*)GetEngine())->CW4_TM.UpdateTile(GetEngine(), 2, 8, 0);
			preLife = ((CW4Engine*)GetEngine())->blood;
			lifeTime = 300;
		}
	}
	
	preTime = iCurrentTime;
}
