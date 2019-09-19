#include "Light.h"

Light::Light():
	_flagVisualise(false), _showLight0(false), _showLight1(false), _showLight2(false), _showLight3(true)
{
	/*====================================================================================
	* AMBIENT PARAMETER (r,g,b,a)
	*====================================================================================*/
	// Ambient light is the basic uniform lighting that a source gives up, regardless of
	// direction. Normally, this is set to a low intensity version of the diffuse colour.
	static GLfloat ambient[] =
	{
		// LIGHT 0 (dull yellow)
		0.15f, 0.15f, 0.0f, 1.0f,
		// LIGHT 1 (dark red)
		0.25f, 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (dark green)
		0.0f, 0.15f, 0.0f, 1.0f,
		// LIGHT 3 (dark blue)
		0.0f, 0.0f, 0.05f, 1.0f
	};
	_ambient = ambient;
	/*====================================================================================
	* DIFFUSE PARAMETER (r,g,b,a)
	*====================================================================================*/
	// Diffuse is the main lighting colour, that is dependent of directional parameters.
	static GLfloat diffuse[] =
	{
		// LIGHT 0 (yellow)
		0.5f, 0.5f, 0.0f, 1.0f,
		// LIGHT 1 (bright red)
		0.8f, 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (deep green)
		0.0f, 0.8f, 0.0f, 1.0f,
		// LIGHT 3 (bright blue)
		0.0f, 0.0f, 0.8f, 1.0f
	};
	_diffuse = diffuse;
	/*===================================================================================
	* SPECULAR PARAMETER (r,g,b,a)
	*====================================================================================*/
	// The specular parameter describes the colour of specular highlights (controlled by
	// the shininess material value of the surface).
	static GLfloat specular[] =
	{
		// LIGHT 0 (bright white)
		1.0f, 1.0f, 1.0f, 1.0f,
		// LIGHT 1 (bright red)
		1.0f, 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (bright green)
		0.0f, 1.0f, 0.0f, 1.0f,
		// LIGHT 3 (bright blue)
		0.0f, 0.0f, 1.0f, 1.0f
	};
	_specular = specular;
}


Light::~Light()
{
}

void Light::Display() {
	// If light source visualisation off, do not display.
	if (!_flagVisualise) return;

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glDisable(GL_LIGHTING);

	if (_showLight0)
	{
		// Draw LIGHT 1 (yellow light)
		glPushMatrix();
		glColor4fv(&_diffuse[_LIGHT_0]);
		glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}

	if (_showLight1)
	{
		// Draw LIGHT 1 (red light)
		glPushMatrix();
		glColor4fv(&_diffuse[_LIGHT_1]);
		glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}

	if (_showLight2)
	{
		// Draw LIGHT 2 (green light)
		glPushMatrix();
		glColor4fv(&_diffuse[_LIGHT_2]);
		glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}

	if (_showLight3)
	{
		// Draw LIGHT 3 (blue light)
		glPushMatrix();
		glColor4fv(&_diffuse[_LIGHT_3]);
		glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
	glPopMatrix();
}

void Light::Update(const double& deltaTime)
{
	//when light is off
	if (_flagVisualise == false) {
		return;
	}

	// Enable lighting to display effects of these lights by default
	glEnable(GL_LIGHTING);

	/*===================================================================================
	* LIGHT 0 : Yellow Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT0, GL_AMBIENT, &_ambient[_LIGHT_0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &_diffuse[_LIGHT_0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &_specular[_LIGHT_0]);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight0 ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);

	/*===================================================================================
	* LIGHT 1 : Red Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT1, GL_AMBIENT, &_ambient[_LIGHT_1]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, &_diffuse[_LIGHT_1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, &_specular[_LIGHT_1]);
	// Set the lights attentuation i.e. how quickly the light fades as it moves away
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0025f);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight1 ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

	/*===================================================================================
	* LIGHT 2 : Green Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT2, GL_AMBIENT, &_ambient[_LIGHT_2]);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, &_diffuse[_LIGHT_2]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, &_specular[_LIGHT_2]);
	// Set the lights attentuation i.e. how quickly the light fades as it moves away
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0025f);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight2 ? glEnable(GL_LIGHT2) : glDisable(GL_LIGHT2);

	/*===================================================================================
	* LIGHT 3 : Blue Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT3, GL_AMBIENT, &_ambient[_LIGHT_3]);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, &_diffuse[_LIGHT_3]);
	glLightfv(GL_LIGHT3, GL_SPECULAR, &_specular[_LIGHT_3]);
	// Set the lights attentuation i.e. how quickly the light fades as it moves away
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0005f);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight3 ? glEnable(GL_LIGHT3) : glDisable(GL_LIGHT3);
}

void Light::HandleKey(unsigned char key, int state, int x, int y)
{
	// Ignore callback from key release (state == 0)
	if (!state) return;

	switch (key)
	{
	case '0':
		_showLight0 = _showLight1 = _showLight2 = _showLight3 = false;
		break;
	case '1':
		_showLight0 = true;
		_showLight1 = _showLight2 = _showLight3 = false;
		break;
	case '2':
		_showLight1 = true;
		_showLight0 = _showLight2 = _showLight3 = false;
		break;
	case '3':
		_showLight2 = true;
		_showLight1 = _showLight0 = _showLight3 = false;
		break;
	case '4':
		_showLight3 = true;
		_showLight1 = _showLight2 = _showLight0 = false;
		break;
	case 'p':
		_flagVisualise = false;
		glDisable(GL_LIGHTING);
		break;
	case 'o':
		_flagVisualise = true;
		glEnable(GL_LIGHTING);
		break;
	}
}
