#include "Skybox.h"

Skybox::Skybox()
{
	texID = Scene::GetTexture("./Textures/bg.bmp");
}

Skybox::~Skybox()
{
}

void Skybox::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	glNormal3f(1.f, 0.f, 0.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(-1.f, -1.f, -1.f);
	}
	glEnd();

	glNormal3f(-1.f, 0.f, 0.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, -1.f, 1.f);
	}
	glEnd();

	glNormal3f(0.f, 0.f, 1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, -1.f, -1.f);
	}
	glEnd();

	glNormal3f(0.f, 0.f, -1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(-1.f, -1.f, 1.f);
	}
	glEnd();

	glNormal3f(0.f, -1.f, 0.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, 1.f, -1.f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
