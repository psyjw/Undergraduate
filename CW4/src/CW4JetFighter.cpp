#include "header.h"
#include "templates.h"
#include "CW4JetFighter.h"



CW4JetFighter::CW4JetFighter(CW4Engine* pEngine, int width, int height, int direction, int spawnTime) :CW4Enemy(pEngine, width, height, direction, true, spawnTime)
{
	enemyType = 0;
	enemy[0].LoadImage("heli.png");
	score = "10";
	
}

CW4JetFighter::CW4JetFighter(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int Pretime) :CW4Enemy(pEngine, iX, iY, direction, Status, Firerate, visible, Enemytype, Pretime)
{
	enemyType = Enemytype;
	enemy[0].LoadImage("heli.png");
	score = "10";
	
}

CW4JetFighter::~CW4JetFighter()
{
}


void CW4JetFighter::DoUpdate(int iCurrentTime)
{
	if (((CW4Engine*)GetEngine())->isPause == true) {
		preTime = iCurrentTime;
		return;
	}
	fireRate = fireRate - (iCurrentTime - preTime);
	preTime = iCurrentTime;
	if (side == 0) {
		m_iCurrentScreenX = m_iCurrentScreenX + 4 * leftX;

		if (m_iCurrentScreenX <= 320)
			leftX = 1;
		if (m_iCurrentScreenX >= 640)
			leftX = -1;
	}
	else {
		m_iCurrentScreenX = m_iCurrentScreenX + 4 * rightX;

		if (m_iCurrentScreenX <= 640)
			rightX = 1;
		if (m_iCurrentScreenX >= 960)
			rightX = -1;
	}

	if (fireRate <= 0) {
		this->attack(m_iCurrentScreenX, m_iCurrentScreenY);
		fireRate = 3000;
		
	}
	RedrawObjects();
}
