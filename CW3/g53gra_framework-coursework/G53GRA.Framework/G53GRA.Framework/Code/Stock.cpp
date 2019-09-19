#include "Stock.h"

Stock::Stock()
{
	texID = Scene::GetTexture("./Textures/stock.bmp");
}


Stock::~Stock()
{
}

void Stock::Display() {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glColor3f(0.702f, 0.467f, 0.239f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	char curr;

	for (unsigned int i = 0; i < sequence.size(); i++)
	{
		curr = sequence[i];             // for each char in sequence
		switch (curr) {                  // check current char command
		case 'f':                   // draw branch, move forward
			branch(3.f, 0.35f);
			break;
		case '+':                   // yaw clockwise
			glRotatef(-angle, 0.f, 0.f, 1.f);
			break;
		case '/':                   // roll upside-down
			glutSolidSphere(0.35f, 144, 144);
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

void Stock::branch(float h, float radius)
{
	float res = 0.1f*M_PI;                  // resolution (in radians: equivalent to 18 degrees)
	float r = radius;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glNormal3f(cos(t), 0.f, sin(t));
		glBegin(GL_QUADS);
		// Create first points
		glTexCoord2f(0.f, 0.f);
		glVertex3f(x, 0.f, z);          // bottom
		glTexCoord2f(0.f, 1.f);
		glVertex3f(x, h, z);          // top
										// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		glTexCoord2f(1.f, 1.f);
		glVertex3f(x, h, z);          // top
		glTexCoord2f(1.f, 0.f);
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, h, 0.f);            // translate to top of branch
}

void Stock::Update(const double& deltaTime) {
	if (status != substatus) {
		moving[2] = true;
		if (substatus == 0) {
			pos[0] -= static_cast<float>(deltaTime) * 1.f;
			if (pos[0] <= -21.f) {
				substatus = 1;
				moving[2] = false;
			}
		}
		else {
			pos[0] += static_cast<float>(deltaTime) * 1.f;
			if (pos[0] >= -16.f) {
				substatus = 0;
				pos[0] = -16.f;
				moving[2] = false;
			}
		}
	}
}