#include "Body.h"

Body::Body()
{
}

Body::Body(GLint bodyID) : Body() {
	frontID = bodyID;
}

Body::~Body()
{
}

void Body::Display() {
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_TEXTURE_2D);

	front();
	top();
	back();
	bottom();
	left();
	right();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Body::front() {
	glBindTexture(GL_TEXTURE_2D, frontID);

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-10.f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-10.f, -1.5f, 0.5f);
	glTexCoord2f(0.375f, 0.f);
	glVertex3f(-6.25f, -1.5f, 0.5f);
	glTexCoord2f(0.375f, 1.f);
	glVertex3f(-6.25f, 0.5f, 0.5f);
	glEnd();

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);	
	glTexCoord2f(0.375f, 1.f);
	glVertex3f(-6.25f, 0.5f, 0.5f);
	glTexCoord2f(0.375f, 0.875f);
	glVertex3f(-6.25f, 0.25f, 0.5f);	
	glTexCoord2f(0.635f, 0.875f);
	glVertex3f(-3.25f, 0.25f, 0.5f);
	glTexCoord2f(0.635f, 0.1f);
	glVertex3f(-3.25f, 0.5f, 0.5f);
	glEnd();

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.375f, 0.35f);
	glVertex3f(-6.25f, -0.8f, 0.5f);
	glTexCoord2f(0.375f, 0.f);
	glVertex3f(-6.25f, -1.5f, 0.5f);
	glTexCoord2f(0.635f, 0.f);
	glVertex3f(-3.25f, -1.5f, 0.5f);
	glTexCoord2f(0.635f, 0.35f);
	glVertex3f(-3.25f, -0.8f, 0.5f);
	glEnd();

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.635f, 1.f);
	glVertex3f(-3.25f, 0.5f, 0.5f);
	glTexCoord2f(0.635f, 0.f);
	glVertex3f(-3.25f, -1.5f, 0.5f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(0.f, -1.5f, 0.5f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(0.f, 0.5f, 0.5f);
	glEnd();
}

void Body::top() {
	texID = Scene::GetTexture("./Textures/bodyTop.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, 1.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-10.f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-10.f, 0.5f, 0.5f);
	glTexCoord2f(0.9f, 0.f);
	glVertex3f(0.f, 0.5f, 0.5f);
	glTexCoord2f(0.9f, 1.f);
	glVertex3f(0.f, 0.5f, -0.5f);
	glEnd();
}

void Body::back() {
	texID = Scene::GetTexture("./Textures/bodyBack.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, 0.f, -1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-10.f, -1.5f, -0.5f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-10.f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0.f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(0.f, -1.5f, -0.5f);
	glEnd();
}

void Body::bottom() {
	texID = Scene::GetTexture("./Textures/bodyBottom.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(0.f, -1.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-10.f, -1.5f, 0.5f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-10.f, -1.5f, -0.5f);
	glTexCoord2f(1.f, 0.95f);
	glVertex3f(0.f, -1.5f, -0.5f);
	glTexCoord2f(0.f, 0.95f);
	glVertex3f(0.f, -1.5f, 0.5f);
	glEnd();
}

void Body::left() {
	texID = Scene::GetTexture("./Textures/bodyLeft.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(-1.f, 0.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-10.f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(-10.f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-10.f, -1.5f, -0.5f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-10.f, -1.5f, 0.5f);
	glEnd();
}

void Body::right() {
	texID = Scene::GetTexture("./Textures/bodyRight.bmp");
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(1.f, 0.f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(0.f, 0.5f, -0.5f);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0.f, 0.5f, 0.5f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(0.f, -1.5f, 0.5f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(0.f, -1.5f, -0.5f);
	glEnd();
}

void Body::HandleKey(unsigned char key, int state, int mx, int my) {
	if ((moving[0] || moving [1] || moving[2] || moving[3] || shooting[0] || shooting[1] || shooting[2] || shooting[3]) == true) {
		return;
	}
	else {
		switch (key) {
		case 'M':
		case 'm':
			status = 1;
			break;
		case 'N':
		case 'n':
			status = 0;
			break;
		case 'Z':
		case 'z':
			if (status == 0) {
				shooting[0] = true;
				shooting[1] = true;
				shooting[2] = true;
				shooting[3] = true;
			}
			break;
		default:
			break;
		}
	}
}
