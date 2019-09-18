#include "header.h"
#include "templates.h"
#include "Psyjw19Object2.h"



Psyjw19Object2::Psyjw19Object2(BaseEngine* pEngine) :DisplayableObject(pEngine)
, towardsX(1)
, towardsY(1)
, iColor(0xFF0000)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 0;
	m_iCurrentScreenY = m_iPreviousScreenY = 0;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	// And make it visible
	SetVisible(true);
}


Psyjw19Object2::~Psyjw19Object2()
{
}

void Psyjw19Object2::Draw()
{
	GetEngine()->DrawForegroundOval(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth - 1, m_iCurrentScreenY + m_iDrawHeight - 1, iColor);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	//StoreLastScreenPositionForUndraw();
}

void Psyjw19Object2::DoUpdate(int currentTime)
{
	int colors[] = {0xFF0000, 0xFFA500, 0xFFFF00, 0x008000, 0x00FFFF, 0x0000FF, 0x800080};
	int time = currentTime / 1000;
	int perTime = time % 7;
	iColor = colors[perTime];

	m_iCurrentScreenX = m_iCurrentScreenX + 8 * towardsX;
	m_iCurrentScreenY = m_iCurrentScreenY + 6 * towardsY;

	if (m_iCurrentScreenX <= 0)
		towardsX = 1;
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth)
		towardsX = -1;
	if (m_iCurrentScreenY <= 0)
		towardsY = 1;
	if (m_iCurrentScreenY >= GetEngine()->GetWindowHeight() - m_iDrawHeight)
		towardsY = -1;

	RedrawObjects();
}



