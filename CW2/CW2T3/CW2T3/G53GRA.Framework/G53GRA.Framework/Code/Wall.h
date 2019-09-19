#pragma once
#include "DisplayableObject.h"

class Wall :
	public DisplayableObject
{
public:
	Wall(){};
	~Wall(){};

	void Display();
};
