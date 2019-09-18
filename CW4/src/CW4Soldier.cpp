#include "header.h"
#include "templates.h"
#include "CW4Soldier.h"



CW4Soldier::CW4Soldier(CW4Engine* pEngine, int width, int height, int direction, int spawnTime) :CW4Enemy(pEngine, width, height, direction, true, spawnTime)
{
	enemyType = 1;
	enemy[0].LoadImage("soldier.png");
	score = "15";
}

CW4Soldier::CW4Soldier(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int Pretime) :CW4Enemy(pEngine, iX, iY, direction, Status, Firerate, visible, Enemytype, Pretime)
{
	enemyType = 1;
	enemy[0].LoadImage("soldier.png");
	score = "15";
}

CW4Soldier::~CW4Soldier()
{
}


void CW4Soldier::DoUpdate(int iCurrentTime)
{
	if (((CW4Engine*)GetEngine())->isPause == true) {
		preTime = iCurrentTime;
		return;
	}
	fireRate = fireRate - (iCurrentTime - preTime);
	preTime = iCurrentTime;
	if (side == 0) {
		m_iCurrentScreenX = m_iCurrentScreenX + 6 * leftX;

		if (m_iCurrentScreenX <= 400)
			leftX = 1;
		if (m_iCurrentScreenX >= 640)
			leftX = -1;
	}
	else {
		m_iCurrentScreenX = m_iCurrentScreenX + 6 * rightX;

		if (m_iCurrentScreenX <= 640)
			rightX = 1;
		if (m_iCurrentScreenX >= 880)
			rightX = -1;
	}

	if (fireRate <= 0) {
		this->attack(m_iCurrentScreenX, m_iCurrentScreenY);
		fireRate = 3000;
		
	}

}
