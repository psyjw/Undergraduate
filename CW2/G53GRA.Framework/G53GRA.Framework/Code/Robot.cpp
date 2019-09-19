#include "Robot.h"

Robot::Robot()
{
}

// define display function (to beD called by MyScene)
void Robot::Display()
{
	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);   // position
	glScalef(scale[0], scale[1], scale[2]); // scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);  // set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);  // set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);  // set orientation (X)

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
		case '-':                   // yaw counter-clockwise
			glRotatef(angle, 0.f, 0.f, 1.f);
			break;
		case '^':                   // pitch clockwise
			glRotatef(-angle, 1.f, 0.f, 0.f);
			break;
		case '&':                   // pitch counter-clockwise
			glRotatef(angle, 1.f, 0.f, 0.f);
			break;
		case '<':	// move head up a bit
			glTranslatef(0.f, 1.f, 0.f);
			break;
		case '>':	//scale to proper size
			glScalef(5.f, 1.f, 5.f);
			break;
		case '|':	// draw head
			glutWireSphere(1.f, 144, 144);
			break;
		case '[':   // "Save"
			glPushMatrix();
			break;
		case ']':   // "Restore"
			glPopMatrix();
			break;
		}
	}
}

void Robot::branch()
{
	glColor3f(0.58f, 0.27f, 0.21f);         // set face colour to brown (rgb)

	float res = 0.1f*(float)M_PI;                  // resolution (in radians: equivalent to 18 degrees)
	float r = 0.15f;                        // ratio of radius to height
	float x = r, z = 0.f;                   // initialise x and z on right of cylinder centre
	float t = 0.f;                          // initialise angle as 0

	do
	{                                     // create branch with multiple QUADS
		glBegin(GL_QUADS);
		// Create first points
		glVertex3f(x, 0.f, z);          // bottom
		glVertex3f(x, 1.f, z);          // top
										// Iterate around circle
		t += res;                       // add increment to angle
		x = r * cos(t);                   // move x and z around circle
		z = r * sin(t);
		// Close quad
		glVertex3f(x, 1.f, z);          // top
		glVertex3f(x, 0.f, z);          // bottom
		glEnd();
	} while (t <= 2 * M_PI);                // full rotation around circle

	glTranslatef(0.f, 1.f, 0.f);            // translate to top of branch
}

void Robot::getSequence()
{
	int gen = 0, j = 0;
	string next;
	bool changed;
	sequence = init;
	char curr;
	while (gen < iter) {                     // Iterative scheme
		next = "";                          // Start with blank
		for (unsigned int i = 0; i < sequence.size(); i++) {
			curr = sequence[i];             // For each letter in the sequence
			changed = false;
			j = 0;
			for (vector<char>::iterator it = flags.begin(); it != flags.end(); ++it, j++) {
				if (curr == *it) {           // Iterate through vector of 'flags'
					next += change[j];      // Replace flag with corresponding change string
					changed = true;
					break;
				}
			}
			if (!changed)                   // If current char does not match a flag
				next += curr;               // ... add it to sequence string
		}
		sequence = next;                    // Update sequence string
		gen++;                              // Recurse
	}
}
