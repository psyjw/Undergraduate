#include "Shell.h"

Shell::Shell()
{
	texID = Scene::GetTexture("./Textures/shell.bmp");
}

Shell::~Shell()
{
}

void Shell::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]); // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(0.62f, 0.533f, 0.329f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	char curr;

	for (unsigned int i = 0; i < sequence.size(); i++)
	{
		curr = sequence[i];             // for each char in sequence
		switch (curr) {                  // check current char command
		case 'f':                   // draw branch, move forward
			branch();
			break;
		case '+':                   // yaw clockwise
			glRotatef(-angle, 0.f, 0.f, 1.f);
			break;
		case '>':                   //roll counter-clockwise
			glRotatef(angle, 0.f, 1.f, 0.f);
			break;
		case '|':                   // draw bottom and top
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0.204f, 0.180f, 0.145f);
			glutSolidCone(0.25f, 0.1f, 144, 144);
			glPopAttrib();
			break;
		case '[':   // "Save"
			glPushMatrix();
			break;
		case ']':   // "Restore"
			glPopMatrix();
			break;
		}
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Shell::branch()
{
	float res = 0.1f*M_PI;                  // resolution (in radians: equivalent to 18 degrees)
	float r = 0.25f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		// Create first points
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, 0.f, z);          // bottom
		glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 1.5f, z);          // top
										// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		glTexCoord2f(1.f, 1.f);
		glVertex3f(x, 1.5f, z);          // top
		glTexCoord2f(0.f, 1.f);
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, 1.5f, 0.f);            // translate to top of branch
}

void Shell::Update(const double& deltaTime) {
	if (shooting[3] == true) {
		if (pos[1] <= 11.5f && half == false) {
			pos[1] += static_cast<float>(deltaTime) * 0.5f;
		}
		else {
			half = true;
			pos[1] -= static_cast<float>(deltaTime) * 1.f;
		}
		pos[2] += static_cast<float>(deltaTime) * 0.5f;

		if (pos[2] >= 5.f) {
			shooting[3] = false;
			half = false;
			pos[1] = 10.f;
			pos[2] = 0.f;
		}
	}
}
