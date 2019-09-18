#include "header.h"
#include "templates.h"
#include "Psyjw19Text.h"


Psyjw19Text::Psyjw19Text(BaseEngine* pEngine) :DisplayableObject(pEngine)
, text("red")
{
	SetVisible(true);
}


Psyjw19Text::~Psyjw19Text()
{
}


void Psyjw19Text::Draw()
{
	GetEngine()->DrawForegroundString(350, 540, text, 0xFFFFFF, NULL);
	GetEngine()->Redraw(true);
}


void Psyjw19Text::DoUpdate(int currentTime)
{
	char* texts[] = { "red", "orange", "yellow", "green", "cyan", "blue", "purple"};
	int time = currentTime / 1000;
	int perTime = time % 7;
	
	text = texts[perTime];
	
	
	RedrawObjects();
}
