#pragma once
#include "DisplayableObject.h"
#include "Input.h"
#include <string>
class Body :
	public DisplayableObject,
	public Input
{
public:
	Body();
	Body(GLint bodyID);
	~Body();
	void Display();
	void HandleKey(unsigned char key, int state, int mx, int my);

private:
	void front();
	void top();
	void back();
	void bottom();
	void left();
	void right();

	GLint frontID;
	GLint texID;
};

