#include "Trigger.h"

Trigger::Trigger()
{
}

Trigger::~Trigger()
{
}

void Trigger::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(0.286f, 0.251f, 0.173f);
	glRotatef(90.f, 1.f, 0.f, 0.f);
	entity();

	glPopMatrix();
}

void Trigger::curvedFront() {
	float res = 0.1f*M_PI / 30;                  // resolution (in radians: equivalent to 18 degrees)
	float x1 = -2.f, z1 = 0.f;                   // initialise x and z on right of cylinder centre
	float x2 = -1.7f, z2 = 0.f;
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(0.f, 0.f, 1.0f);
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x2, 0.15f, z2);          // top
		glVertex3f(x1, 0.15f, z1);          // bottom
										   // Iterate around circle
		t += res;                       // add increment to angle
		x1 = 2 * cos(t - M_PI);                   // move x and z around circle
		x2 = 1.7 * cos(t - M_PI);
		z1 = 2 * sin(t);
		z2 = 1.7 * sin(t);
		// Close quad

		glVertex3f(x1, 0.15f, z1);          // bottom
		glVertex3f(x2, 0.15f, z2);          // top
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Trigger::curvedBack() {
	float res = 0.1f*M_PI / 30;                  // resolution (in radians: equivalent to 18 degrees)
	float x1 = -2, z1 = 0.f;                   // initialise x and z on right of cylinder centre
	float x2 = -1.7f, z2 = 0.f;
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(0.f, 0.f, -1.0f);
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x1, -0.15f, z1);          // bottom
		glVertex3f(x2, -0.15f, z2);          // top
											// Iterate around circle
		t += res;                       // add increment to angle
		x1 = 2 * cos(t - M_PI);                   // move x and z around circle
		x2 = 1.7 * cos(t - M_PI);
		z1 = 2 * sin(t);
		z2 = 1.7 * sin(t);
		// Close quad

		glVertex3f(x2, -0.15f, z2);          // top
		glVertex3f(x1, -0.15f, z1);          // bottom
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Trigger::curvedLeft() {
	float res = 0.1f*M_PI / 30;                  // resolution (in radians: equivalent to 18 degrees)
	float x = -2, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(-cos(t), 0.f, sin(t));
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x, 0.15f, z);          // top
		glVertex3f(x, -0.15f, z);          // bottom
										  // Iterate around circle
		t += res;                       // add increment to angle
		x = 2 * cos(t - M_PI);                   // move x and z around circle
		z = 2 * sin(t);
		// Close quad

		glVertex3f(x, -0.15f, z);          // bottom
		glVertex3f(x, 0.15f, z);          // top
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Trigger::curvedRight() {
	float res = 0.1f*M_PI / 30;                  // resolution (in radians: equivalent to 18 degrees)
	float x = -1.7, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(cos(t), 0.f, -sin(t));
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x, -0.15f, z);          // top
		glVertex3f(x, 0.15f, z);          // bottom
										 // Iterate around circle
		t += res;                       // add increment to angle
		x = 1.7 * cos(t - M_PI);                   // move x and z around circle
		z = 1.7 * sin(t);
		// Close quad

		glVertex3f(x, 0.15f, z);          // bottom
		glVertex3f(x, -0.15f, z);          // top
		glEnd();
	} while (t <= (M_PI / 6));                // 30 degrees around circle
}

void Trigger::entity() {
	curvedFront();
	curvedLeft();
	curvedBack();
	curvedRight();

	glNormal3f(sin(M_PI / 6), 0.f, cos(M_PI / 6));
	glBegin(GL_QUADS);
	glVertex3f(-1.47f, 0.15f, 0.85f);
	glVertex3f(-1.73f, 0.15f, 1.f);
	glVertex3f(-1.73f, -0.15f, 1.f);
	glVertex3f(-1.47f, -0.15f, 0.85f);
	glEnd();

	glNormal3f(0.f, 1.f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-2.f, 0.15f, 0.f);
	glVertex3f(-1.7f, 0.15f, 0.f);
	glVertex3f(-1.7f, -0.15f, 0.f);
	glVertex3f(-2.f, -0.15f, 0.f);
	glEnd();
}

void Trigger::Update(const double& deltaTime) {
	if (shooting[1] == true) {
		if (pos[0] >= -7.5f && half == false) {
			pos[0] -= static_cast<float>(deltaTime) * 0.5f;
		}
		else {
			half = true;
			pos[0] += static_cast<float>(deltaTime) * 0.5f;
			if (pos[0] >= -7.f) {
				shooting[1] = false;
				half = false;
				pos[0] = -7.f;
			}
		}
	}
}