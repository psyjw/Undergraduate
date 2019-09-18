#include "header.h"
#include "templates.h"
#include "CW4ScoreBoard.h"



CW4ScoreBoard::CW4ScoreBoard(CW4Engine* pEngine) :DisplayableObject(pEngine)
{
	engine = pEngine;
	SetVisible(true);
}

CW4ScoreBoard::CW4ScoreBoard(CW4Engine* pEngine, int Bgx) :DisplayableObject(pEngine)
{
	engine = pEngine;
	bgX = Bgx;
	SetVisible(true);
}

CW4ScoreBoard::~CW4ScoreBoard()
{
}


void CW4ScoreBoard::Draw()
{
	GetEngine()->DrawForegroundString(80, 640, "Life: ", 0xFFFFFF, NULL);
	GetEngine()->DrawForegroundString(160, 640, life.c_str(), 0xFFFFFF, NULL);
	GetEngine()->DrawForegroundString(320, 640, engine->name, 0xFFFFFF, NULL);
	GetEngine()->DrawForegroundString(640, 640, "Enemy Units Eliminitaed: ", 0xFFFFFF, NULL);
	GetEngine()->DrawForegroundString(1000, 640, score.c_str(), 0xFFFFFF, NULL);
	GetEngine()->DrawForegroundString(640, 680, "Magazine: ", 0xFFFFFF, NULL);
	GetEngine()->DrawForegroundString(800, 680, magazine.c_str(), 0xFFFFFF, NULL);
	GetEngine()->Redraw(true);
}


void CW4ScoreBoard::DoUpdate(int iCurrentTime)
{
	if (((CW4Engine*)GetEngine())->isPause == true) {
		return;
	}
	life = std::to_string(engine->blood);
	score = std::to_string(engine->enemyKill);
	magazine = std::to_string(engine->lastMag);
	
	if (engine->enemyKill >= 100 && bgX < 0) {
		bgX = bgX + 10;
		engine->bg.RenderImageWithMask(engine->GetBackground(), 0, 0, bgX, 0, engine->bg.GetWidth(), engine->bg.GetHeight());
	}

	if (engine->blood == 0) {
		engine->state = 4;
		engine->SetupBackgroundBuffer();
	}
	if (engine->enemyKill >= 1000) {
		engine->state = 3;
		engine->SetupBackgroundBuffer();
	}

	RedrawObjects();
}


string CW4ScoreBoard::save()
{
	return to_string(bgX);
}
