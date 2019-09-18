#include "header.h"
#include "templates.h"
#include "CW4Enemy.h"
#include "CW4Bullet.h"
#include <iostream>

using namespace std;

CW4Enemy::CW4Enemy(CW4Engine* pEngine, int width, int height, int direction, bool visible, int spawnTime) :DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = width;
	m_iCurrentScreenY = m_iPreviousScreenY = height;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 150;
	m_iDrawHeight = 150;

	side = direction;
	preTime = spawnTime;
	engine = pEngine;
	enemy[1].LoadImage("explosive.jpg");
	
	// And make it visible
	SetVisible(visible);

}

CW4Enemy::CW4Enemy(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int Pretime) :DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 150;
	m_iDrawHeight = 150;

	side = direction;
	state = Status;
	fireRate = Firerate;
	preTime = Pretime;
	engine = pEngine;
	enemy[1].LoadImage("explosive.jpg");
	// And make it visible
	SetVisible(visible);

}


CW4Enemy::~CW4Enemy()
{
}



void CW4Enemy::Draw()
{
	
	if (this->IsVisible()) {
		
		enemy[state].RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX - enemy[state].GetWidth() / 2, m_iCurrentScreenY - enemy[state].GetHeight() / 2, enemy[state].GetWidth(), enemy[state].GetHeight());
		GetEngine()->DrawForegroundString(m_iCurrentScreenX - enemy[state].GetWidth() / 2, m_iCurrentScreenY - enemy[state].GetHeight() / 2, score, 0xFF0000, NULL);
		GetEngine()->Redraw(true);
	}
}


bool CW4Enemy::eliminate(int iX, int iY)
{
	if (iX <= m_iCurrentScreenX + enemy[state].GetWidth() / 2 && iX >= m_iCurrentScreenX - enemy[state].GetWidth() / 2) {
		if (iY <= m_iCurrentScreenY + enemy[state].GetHeight() / 2 && iY >= m_iCurrentScreenY - enemy[state].GetHeight() / 2) {
			return true;
		}
	}
	return false;
}


void CW4Enemy::attack(int iX, int iY)
{
	if (IsVisible() == false) {
		return;
	}
	CW4Bullet* enemyAttack = new CW4Bullet((CW4Engine*)GetEngine(), 0, iX, iY, 0);
	if (engine->bulletIndex > 14) {
		engine->bulletIndex = 8;
		GetEngine()->StoreObjectInArray(engine->bulletIndex, enemyAttack);
	}
	else {
		GetEngine()->StoreObjectInArray(engine->bulletIndex, enemyAttack);
	}
	
	engine->bulletIndex = engine->bulletIndex + 1;

	
}



int CW4Enemy::getY()
{
	return this->m_iCurrentScreenY;
}


int CW4Enemy::getX()
{
	return this->m_iCurrentScreenX;
}


string CW4Enemy::save()
{
	/*cout << to_string(m_iCurrentScreenX) << " " <<  to_string(m_iCurrentScreenY) << " " << to_string(side) << " " << to_string(state) << " "*/
	return to_string(m_iCurrentScreenX) + " " + to_string(m_iCurrentScreenY) + " " + to_string(side) + " " + to_string(state) + " " + to_string(fireRate) + " " + to_string(IsVisible()) + " " + to_string(enemyType) + " " + to_string(preTime);
}
