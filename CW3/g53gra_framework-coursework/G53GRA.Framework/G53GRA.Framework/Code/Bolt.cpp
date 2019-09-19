#include "Bolt.h"

Bolt::Bolt()
{
}

Bolt::Bolt(GLint bodyID) : Bolt() {
	texID = bodyID;
}

Bolt::~Bolt()
{
}

void Bolt::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.375f, 0.875f);
	glVertex3f(-6.25f, 0.25f, 0.499f);
	glTexCoord2f(0.375f, 0.35f);
	glVertex3f(-6.25f, -0.8f, 0.499f);
	glTexCoord2f(0.635f, 0.35f);
	glVertex3f(-3.25f, -0.8f, 0.499f);
	glTexCoord2f(0.635f, 0.975f);
	glVertex3f(-3.25f, 0.25f, 0.499f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Bolt::Update(const double& deltaTime) {
	if (shooting[0] == true) {
		if (pos[0] >= -2.0f && half == false) {
			pos[0] -= static_cast<float>(deltaTime) * 1.f;
		}
		else {
			half = true;
			pos[0] += static_cast<float>(deltaTime) * 1.f;
			if (pos[0] >= 0.f) {
				shooting[0] = false;
				half = false;
				pos[0] = 0.f;
			}
		}
	}
}