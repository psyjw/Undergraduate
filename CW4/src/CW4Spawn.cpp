#include "header.h"
#include "templates.h"
#include "CW4Spawn.h"
#include <iostream>


CW4Spawn::CW4Spawn(CW4Engine* pEngine) :DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 0;
	m_iCurrentScreenY = m_iPreviousScreenY = 0;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 0;
	m_iDrawHeight = 0;
	// And make it visible
	SetVisible(false);
}

CW4Spawn::CW4Spawn(CW4Engine* pEngine, int Timediff, int Pretime, int Enemynum, int Enemyindex) :DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 0;
	m_iCurrentScreenY = m_iPreviousScreenY = 0;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 0;
	m_iDrawHeight = 0;
	// And make it visible
	SetVisible(false);
	timeDiff = Timediff;
	preTime = Pretime;
	enemyNum = Enemynum;
	enemyIndex = Enemyindex;
}

CW4Spawn::~CW4Spawn()
{
}




void CW4Spawn::DoUpdate(int iCurrentTime)
{
	
	if (((CW4Engine*)GetEngine())->isPause == true) {
		preTime = iCurrentTime;
		return;
	}

	timeDiff = timeDiff - (iCurrentTime - preTime);
	preTime = iCurrentTime;
	if ( timeDiff <= 0 && enemyNum < 5) {
		
		timeDiff = 1000;
		
		for (int i = 3; i < 8; i++) {
			if (GetEngine()->GetDisplayableObject(i)->IsVisible() == false) {
				enemyIndex = i;
				break;
			}
		}
		
		enemyType = rand() % 3;
		
		if (enemyType == 0) {
				if (rand() % 2) {
					
					GetEngine()->StoreObjectInArray(enemyIndex, new CW4JetFighter((CW4Engine*)GetEngine(), -60, 160, 0, iCurrentTime));
				}
				else {
					
					GetEngine()->StoreObjectInArray(enemyIndex, new CW4JetFighter((CW4Engine*)GetEngine(), 1340, 160, 1, iCurrentTime));
				}	
		}
		else if (enemyType == 1) {
				if (rand() % 2) {
					
					GetEngine()->StoreObjectInArray(enemyIndex, new CW4Soldier((CW4Engine*)GetEngine(), -60, 400, 0, iCurrentTime));
				}
				else {
					
					GetEngine()->StoreObjectInArray(enemyIndex, new CW4Soldier((CW4Engine*)GetEngine(), 1340, 400, 1, iCurrentTime));
				}
		}
		else {
				if (rand() % 2) {
					
					GetEngine()->StoreObjectInArray(enemyIndex, new CW4Tank((CW4Engine*)GetEngine(), -60, 400, 0, iCurrentTime));
				}
				else {
					
					GetEngine()->StoreObjectInArray(enemyIndex, new CW4Tank((CW4Engine*)GetEngine(), 1340, 400, 1, iCurrentTime));
				}
		}
		enemyNum = enemyNum + 1;
	}
	RedrawObjects();
}


string CW4Spawn::save()
{
	 /*cout << to_string(timeDiff) << " " << to_string(preTime) << " " << to_string(enemyNum) << " " << to_string(enemyIndex) << endl;*/
	return to_string(timeDiff) + " " + to_string(preTime) + " " + to_string(enemyNum) + " " + to_string(enemyIndex);
}
