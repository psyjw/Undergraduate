#include "Scope.h"

Scope::Scope()
{
}

Scope::~Scope()
{
}

void Scope::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]); // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);

	front();
	top();
	back();
	bottom();
	left();
	right();
	glass();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Scope::front() {
	texID = Scene::GetTexture("./Textures/scopefront.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.07f, 0.03f);
	glVertex3f(0.f, 0.f, 0.5f);
	glTexCoord2f(0.35f, 0.03f);
	glVertex3f(1.f, 0.f, 0.5f);
	glTexCoord2f(0.35f, 0.9f);
	glVertex3f(1.f, 2.f, 0.5f);
	glTexCoord2f(0.07f, 0.9f);
	glVertex3f(0.f, 2.f, 0.5f);
	glEnd();

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.35f, 0.03f);
	glVertex3f(1.f, 0.f, 0.5f);
	glTexCoord2f(0.9f, 0.03f);
	glVertex3f(3.f, 0.f, 0.5f);
	glTexCoord2f(0.9f, 0.47f);
	glVertex3f(3.f, 1.f, 0.5f);
	glTexCoord2f(0.35f, 0.47f);
	glVertex3f(1.f, 1.f, 0.5f);
	glEnd();
}

void Scope::top() {
	texID = Scene::GetTexture("./Textures/scopetop.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, 1.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.0f);
	glVertex3f(0.f, 2.f, 0.5f);
	glTexCoord2f(0.37f, 0.f);
	glVertex3f(1.f, 2.f, 0.5f);
	glTexCoord2f(0.37f, 1.f);
	glVertex3f(1.f, 2.f, -0.5f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0.f, 2.f, -0.5f);
	glEnd();

	glNormal3f(0.f, 1.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.45f, 0.2f);
	glVertex3f(0.f, 1.f, 0.5f);
	glTexCoord2f(0.95f, 0.2f);
	glVertex3f(3.f, 1.f, 0.5f);
	glTexCoord2f(0.95f, 0.8f);
	glVertex3f(3.f, 1.f, -0.5f);
	glTexCoord2f(0.45f, 0.8f);
	glVertex3f(0.f, 1.f, -0.5f);
	glEnd();
}

void Scope::back() {
	texID = Scene::GetTexture("./Textures/scopeback.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, 0.f, -1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.65f, 0.4f);
	glVertex3f(1.f, 1.f, -0.5f);
	glTexCoord2f(0.9f, 0.4f);
	glVertex3f(0.f, 1.f, -0.5f);
	glTexCoord2f(0.9f, 1.f);
	glVertex3f(0.f, 2.f, -0.5f);
	glTexCoord2f(0.65f, 1.f);
	glVertex3f(1.f, 2.f, -0.5f);
	glEnd();

	glNormal3f(0.f, 0.f, -1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(3.f, 0.f, -0.5f);
	glTexCoord2f(0.95f, 0.f);
	glVertex3f(0.f, 0.f, -0.5f);
	glTexCoord2f(0.95f, 0.4f);
	glVertex3f(0.f, 1.f, -0.5f);
	glTexCoord2f(0.f, 0.4f);
	glVertex3f(3.f, 1.f, -0.5f);
	glEnd();
}

void Scope::bottom() {
	glNormal3f(0.f, -1.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.65f, 0.4f);
	glVertex3f(0.f, 0.f, 0.5f);
	glTexCoord2f(0.9f, 0.4f);
	glVertex3f(0.f, 0.f, -0.5f);
	glTexCoord2f(0.9f, 1.f);
	glVertex3f(3.f, 0.f, -0.5f);
	glTexCoord2f(0.65f, 1.f);
	glVertex3f(3.f, 0.f, 0.5f);
	glEnd();
}

void Scope::left() {
	texID = Scene::GetTexture("./Textures/scopeleft.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(-1.f, 0.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.5f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(0.f, 1.f, 0.5f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0.f, 1.f, -0.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(0.f, 0.f, -0.5f);
	glEnd();
}

void Scope::right() {
	texID = Scene::GetTexture("./Textures/scoperight.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(1.f, 0.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.1f, 0.f);
	glVertex3f(3.f, 0.f, 0.5f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(3.f, 0.f, -0.5f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(3.f, 1.f, -0.5f);
	glTexCoord2f(0.1f, 1.f);
	glVertex3f(3.f, 1.f, 0.5f);
	glEnd();
}

void Scope::glass() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor4f(0.f, 1.f, 1.f, 0.3f);
	glBegin(GL_QUADS);
	glVertex3f(0.2f, 1.f, 0.5f);
	glVertex3f(0.2f, 2.f, 0.5f);
	glVertex3f(0.2f, 2.f, -0.5f);
	glVertex3f(0.2f, 1.f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.8f, 1.f, 0.5f);
	glVertex3f(0.8f, 2.f, 0.5f);
	glVertex3f(0.8f, 2.f, -0.5f);
	glVertex3f(0.8f, 1.f, -0.5f);
	glEnd();
	glPopAttrib();
}

void Scope::Update(const double& deltaTime) {
	if (status != substatus) {
		moving[1] = true;
		if (substatus == 0) {
			pos[1] += static_cast<float>(deltaTime) * 0.5f;
			if (pos[1] >= 13.f) {
				substatus = 1;
				moving[1] = false;
			}
		}
		else {
			pos[1] -= static_cast<float>(deltaTime) * 0.5f;
			if (pos[1] <= 10.5f) {
				substatus = 0;
				pos[1] = 10.5f;
				moving[1] = false;
			}
		}
	}
}