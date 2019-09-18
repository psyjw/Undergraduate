#include "header.h"
#include "templates.h"
#include "CW4Bullet.h"
#include "CW4Enemy.h"
#include "CW4Spawn.h"

using namespace std;

CW4Bullet::CW4Bullet(CW4Engine* pEngine, int type, int iX, int iY, int targetIndex) :DisplayableObject(pEngine)
{
	if (type == 0) {
		m_iCurrentScreenX = m_iPreviousScreenX = iX;
		m_iCurrentScreenY = m_iPreviousScreenY = iY;
		// The object coordinate will be the top left of the object
		m_iStartDrawPosX = 0;
		m_iStartDrawPosY = 0;
		// Record the ball size as both height and width
		m_iDrawWidth = 6;
		m_iDrawHeight = 6;

		distanceX = iX - 640;
		distanceY = 560 - iY;
	}
	else {
		m_iCurrentScreenX = m_iPreviousScreenX = 640;
		m_iCurrentScreenY = m_iPreviousScreenY = 560;
		// The object coordinate will be the top left of the object
		m_iStartDrawPosX = 0;
		m_iStartDrawPosY = 0;
		// Record the ball size as both height and width
		m_iDrawWidth = 6;
		m_iDrawHeight = 6;

		target = targetIndex;

		destineyY = iY;
		distanceY = 560 - iY;
	}
	
	bullettype = type;
	engine = pEngine;

	bullet[0].LoadImage("enemybullet.png");
	bullet[1].LoadImage("playerbullet.png");
	SetVisible(true);

}

CW4Bullet::CW4Bullet(CW4Engine* pEngine, int iX, int iY, int type, int Distancex, int Distancey, int targetIndex, int Destineyy, bool visible) :DisplayableObject(pEngine)
{
	if (type == 0) {
		m_iCurrentScreenX = m_iPreviousScreenX = iX;
		m_iCurrentScreenY = m_iPreviousScreenY = iY;
		// The object coordinate will be the top left of the object
		m_iStartDrawPosX = 0;
		m_iStartDrawPosY = 0;
		// Record the ball size as both height and width
		m_iDrawWidth = 6;
		m_iDrawHeight = 6;

		distanceX = Distancex;
		distanceY = Distancey;
	}
	else {
		m_iCurrentScreenX = m_iPreviousScreenX = iX;
		m_iCurrentScreenY = m_iPreviousScreenY = iY;
		// The object coordinate will be the top left of the object
		m_iStartDrawPosX = 0;
		m_iStartDrawPosY = 0;
		// Record the ball size as both height and width
		m_iDrawWidth = 6;
		m_iDrawHeight = 6;

		target = targetIndex;

		destineyY = Destineyy;
		distanceY = Distancey;
	}

	bullettype = type;
	engine = pEngine;

	bullet[0].LoadImage("enemybullet.png");
	bullet[1].LoadImage("playerbullet.png");
	SetVisible(visible);

}


CW4Bullet::~CW4Bullet()
{
}


void CW4Bullet::Draw()
{
	
	if (bullettype == 0) {
		if (this->IsVisible()) {
			bullet[0].RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX - bullet[0].GetWidth() / 2, m_iCurrentScreenY - bullet[0].GetHeight() / 2, bullet[0].GetWidth(), bullet[0].GetHeight());
			GetEngine()->Redraw(true);
		}
	}
	else {
		if (this->IsVisible()) {
			bullet[1].RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX - bullet[1].GetWidth() / 2, m_iCurrentScreenY - bullet[1].GetHeight() / 2, bullet[1].GetWidth(), bullet[1].GetHeight());
			GetEngine()->Redraw(true);
		}
	}
}


void CW4Bullet::DoUpdate(int iCurrentTime)
{
	if (engine->isPause == true) {
		return;
	}
	if (IsVisible() == true) {
		if (bullettype == 0) {
			if (m_iCurrentScreenY < 560) {
				m_iCurrentScreenX = m_iCurrentScreenX - distanceX / 60;
				m_iCurrentScreenY = m_iCurrentScreenY + distanceY / 60;
			}
			else {
				if (this->IsVisible() == true) {
					engine->CW4_TM.UpdateTile(engine, 2, 8, 1);
					engine->blood = engine->blood - 1;
					this->SetVisible(false);
				}
			}

		}
		else {

			distanceX = ((CW4Enemy*)(engine->GetDisplayableObject(target)))->getX() - m_iCurrentScreenX;

			if (i > 0) {
				m_iCurrentScreenX = m_iCurrentScreenX + distanceX / i;
				m_iCurrentScreenY = m_iCurrentScreenY - distanceY / 20;
				i = i - 1;
			}
			else {
				if (((CW4Enemy*)(engine->GetDisplayableObject(target)))->state == 0) {
					((CW4Enemy*)(engine->GetDisplayableObject(target)))->state = 1;
					explosionTime = iCurrentTime;
				}
				if (this->IsVisible() == true && iCurrentTime - explosionTime > 100) {
					((CW4Enemy*)(engine->GetDisplayableObject(target)))->SetVisible(false);
					((CW4Spawn*)(engine->GetDisplayableObject(0)))->enemyNum = ((CW4Spawn*)(engine->GetDisplayableObject(0)))->enemyNum - 1;
					engine->enemyKill = engine->enemyKill + atoi(((CW4Enemy*)(engine->GetDisplayableObject(target)))->score);
					engine->isShoot = true;
					this->SetVisible(false);
				}
			}
		}
		RedrawObjects();
	}
	
}


string CW4Bullet::save()
{
	return to_string(m_iCurrentScreenX) + " " + to_string(m_iCurrentScreenY) + " " + to_string(bullettype) + " " + to_string(distanceX) + " " + to_string(distanceY) + " " + to_string(target) + " " + to_string(destineyY) + " " + to_string(IsVisible());
}
