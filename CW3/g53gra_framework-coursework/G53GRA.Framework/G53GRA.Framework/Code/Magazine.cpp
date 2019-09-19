#include "Magazine.h"

Magazine::Magazine()
{
	texID1 = Scene::GetTexture("./Textures/magazine.bmp");
	texID2 = Scene::GetTexture("./Textures/magazineTop.bmp");
	texID3 = Scene::GetTexture("./Textures/magazineBottom.bmp");
}

Magazine::~Magazine()
{
}

void Magazine::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID1);

	glRotatef(90.f, 1.f, 0.f, 0.f);
	entity();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

void Magazine::curvedFront() {
	float res = 0.01*M_PI;                  // resolution (in radians: equivalent to 1.8 degrees)
	float x1 = -5, z1 = 0.f;                   // initialise x and z on right of cylinder centre
	float x2 = -3, z2 = 0.f;
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(0.f, 0.f, 1.0f);
		glBegin(GL_QUADS);
		// Create first points
		glTexCoord2f(1.f, 1.f);
		glVertex3f(x2, 0.5f, z2);          // top
		glTexCoord2f(0.f, 1.f);
		glVertex3f(x1, 0.5f, z1);          // bottom
											// Iterate around circle
		t += res;                       // add increment to angle
		x1 = 5 * cos(t - M_PI);                   // move x and z around circle
		x2 = 3 * cos(t - M_PI);
		z1 = 5 * sin(t);
		z2 = 3 * sin(t);
		// Close quad
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x1, 0.5f, z1);          // bottom
		glTexCoord2f(1.f, 0.f);
		glVertex3f(x2, 0.5f, z2);          // top
		glEnd();
	} while (t <=  (M_PI / 6));                // 30 degrees around circle
}

void Magazine::curvedBack() {
	float res = 0.01f*M_PI;                  // resolution (in radians: equivalent to 18 degrees)
	float x1 = -5, z1 = 0.f;                   // initialise x and z on right of cylinder centre
	float x2 = -3, z2 = 0.f;
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(0.f, 0.f, -1.0f);
		glBegin(GL_QUADS);
		// Create first points
		glTexCoord2f(1.f, 1.f);
		glVertex3f(x1, -0.5f, z1);          // bottom
		glTexCoord2f(0.f, 1.f);
		glVertex3f(x2, -0.5f, z2);          // top
												// Iterate around circle
		t += res;                       // add increment to angle
		x1 = 5 * cos(t - M_PI);                   // move x and z around circle
		x2 = 3 * cos(t - M_PI);
		z1 = 5 * sin(t);
		z2 = 3 * sin(t);
		// Close quad
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x2, -0.5f, z2);          // top
		glTexCoord2f(1.f, 0.f);
		glVertex3f(x1, -0.5f, z1);          // bottom
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Magazine::curvedLeft() {
	float res = 0.01f*M_PI;                  // resolution (in radians: equivalent to 18 degrees)
	float x = -5, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(-cos(t), 0.f, sin(t));
		glBegin(GL_QUADS);
		// Create first points
		glTexCoord2f(1.f, 1.f);
		glVertex3f(x, 0.5f, z);          // top
		glTexCoord2f(0.f, 1.f);
		glVertex3f(x, -0.5f, z);          // bottom
												// Iterate around circle
		t += res;                       // add increment to angle
		x = 5 * cos(t - M_PI);                   // move x and z around circle
		z = 5 * sin(t);
		// Close quad
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, -0.5f, z);          // bottom
		glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 0.5f, z);          // top
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Magazine::curvedRight() {
	float res = 0.01f*M_PI;                  // resolution (in radians: equivalent to 18 degrees)
	float x = -3, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(cos(t), 0.f, -sin(t));
		glBegin(GL_QUADS);
		// Create first points
		glTexCoord2f(1.f, 1.f);
		glVertex3f(x, -0.5f, z);          // top
		glTexCoord2f(0.f, 1.f);
		glVertex3f(x, 0.5f, z);          // bottom
										  // Iterate around circle
		t += res;                       // add increment to angle
		x = 3 * cos(t - M_PI);                   // move x and z around circle
		z = 3 * sin(t);
		// Close quad
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, 0.5f, z);          // bottom
		glTexCoord2f(1.f, 0.f);
		glVertex3f(x, -0.5f, z);          // top
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Magazine::entity() {
	curvedFront();
	curvedLeft();
	curvedBack();
	curvedRight();

	glBindTexture(GL_TEXTURE_2D, texID3);

	glNormal3f(sin(M_PI / 6), 0.f, cos(M_PI / 6));
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-2.6f, 0.5f, 1.5f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-4.33f, 0.5f, 2.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-4.33f, -0.5f, 2.5f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-2.6f, -0.5f, 1.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID2);
	
	glNormal3f(0.f, 1.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-5.f, 0.5f, 0.f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-3.f, 0.5f, 0.f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-3.f, -0.5f, 0.f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-5.f, -0.5f, 0.f);
	glEnd();
}

void Magazine::Update(const double& deltaTime) {
	if (status != substatus) {
		moving[3] = true;
		if (substatus == 0) {
			pos[1] -= static_cast<float>(deltaTime) * 0.5f;
			if (pos[1] <= 6.f) {
				substatus = 1;
				moving[3] = false;
			}
		}
		else {
			pos[1] += static_cast<float>(deltaTime) * 0.5f;
			if (pos[1] >= 8.5f) {
				substatus = 0;
				pos[1] = 8.5f;
				moving[3] = false;
			}
		}
	}
}