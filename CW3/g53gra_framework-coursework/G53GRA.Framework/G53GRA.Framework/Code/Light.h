#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

#define _LIGHT_0 0
#define _LIGHT_1 4
#define _LIGHT_2 8
#define _LIGHT_3 12

class Light :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Light();
	~Light();
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);

private:
	GLfloat *_ambient, *_diffuse, *_specular;
	// flag for showing lights 0-3
	GLboolean _showLight0, _showLight1, _showLight2, _showLight3;
	GLboolean _flagVisualise;
};

