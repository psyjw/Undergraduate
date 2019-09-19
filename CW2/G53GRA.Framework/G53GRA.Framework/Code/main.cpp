/**
* Entry file to framework. Should not edit this file, though to change window size, adjust parameters in creastion of new scene
* <p>
* {@code new MyScene(argc, argv, "title", (const int)width, (const int)height)}
* @author wil
* @date 09/02/16
*/
#include "MyScene.h"
/**
 * Entry method, takes command line arguments and creates new Scene engine to render your G53GRA Coursework
 *
 * @see MyScene
 */

int width = 0;
int height = 0;

bool isSolid = true;	// Use solid or wireframe?

float armRot = 15.f;	// Angle arms are raised
float elbowRot = -15.f; // Angle of elbows
float legRot = 15.f;	// Angle of legs
float kneeRot = -15.f;	// Angle of knees

void setup()
{
	width = 600;                                    // initialise global window variables
	height = 400;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("G53GRA Group 9 Assigment 2");	// create and show window
}

// Draws box of size x, y, z
void drawBox(float x, float y, float z)
{
	glPushMatrix();
	{
		glScalef(x, y, z);
		isSolid ? glutSolidCube(1.f) : glutWireCube(1.f);
	}
	glPopMatrix();
}

// Draw arm (or leg) of robot, will be vertical
void drawArm()
{
	glTranslatef(0.f, -1.5f, 0.f);
	drawBox(1, 3, 1);
}

// Draw head sphere
void drawHead()
{
	glTranslatef(0.f, 1.f, 0.f);
	isSolid ? glutSolidSphere(1.f, 8, 8) : glutWireSphere(1.f, 8, 8);
}

void drawRobot()
{
	glPushMatrix();
	{
		// Body
		drawBox(3.f, 6.f, 2.f);
		// Limbs are named as if the robot is looking towards the camera (negative z-axis)
		// Left Arm
		glPushMatrix();
		{
			glTranslatef(1.5f, 2.f, 1.f);
			glRotatef(armRot, 0.f, 0.f, 1.f);
			drawArm();
			glPushMatrix();
			{
				glTranslatef(0.f, -1.5f, 0.f);
				glRotatef(elbowRot, 0.f, 0.f, 1.f);
				drawArm();
			}
			glPopMatrix();
		}
		glPopMatrix();
		// Right Arm
		glPushMatrix();
		{
			glTranslatef(-1.5f, 2.f, 1.f);
			glRotatef(-armRot, 0.f, 0.f, 1.f);
			drawArm();
			glPushMatrix();
			{
				glTranslatef(0.f, -1.5f, 0.f);
				glRotatef(-elbowRot, 0.f, 0.f, 1.f);
				drawArm();
			}
			glPopMatrix();
		}
		glPopMatrix();
		// Left Leg
		glPushMatrix();
		{
			glTranslatef(.75f, -3.f, 1.f);
			glRotatef(legRot, 0.f, 0.f, 1.f);
			drawArm();
			glPushMatrix();
			{
				glTranslatef(0.f, -1.5f, 0.f);
				glRotatef(kneeRot, 0.f, 0.f, 1.f);
				drawArm();
			}
			glPopMatrix();
		}
		glPopMatrix();
		// Right Leg
		glPushMatrix();
		{
			glTranslatef(-.75f, -3.f, 1.f);
			glRotatef(-legRot, 0.f, 0.f, 1.f);
			drawArm();
			glPushMatrix();
			{
				glTranslatef(0.f, -1.5f, 0.f);
				glRotatef(-kneeRot, 0.f, 0.f, 1.f);
				drawArm();
			}
			glPopMatrix();
		}
		glPopMatrix();
		// Head
		glPushMatrix();
		{
			glTranslatef(0.f, 3.f, 0.f);
			drawHead();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void checkGLError()
{
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}

// Draw robot using a traditional push/pop approach
void draw()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);                   // set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
	glLoadIdentity();                                   // reset drawing

	glTranslatef(0.f, 0.f, -25.f);                      // move drawing further back in the scene

														// Push matrices
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Colour
	glColor3f(.75f, .75f, .75f);

	// Draw
	drawRobot();

	// Pop matrices
	glPopMatrix();
	glPopAttrib();

	checkGLError();
	glutSwapBuffers();                                  // execute all commands, swap buffers
	glutPostRedisplay();								// Update variables
}

void reshape(int _width, int _height)
{
	// update global dimension variables
	width = _width;
	height = _height;
	// calculate new aspect ratio
	GLdouble aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();     // reset matrix
	gluPerspective(45.0, aspect, 1, 1000);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW); // return matrix mode to modelling and viewing
}

int main(int argc, char* argv[])
{
	// Create new instance of MyScene - the OpenGL context on which your coursework is built
	MyScene *scene = NULL;
	scene = new MyScene(argc, argv, "G53GRA", static_cast<const int>(600), static_cast<const int>(400));

	// Begin the main GL loop
	scene->Run();

	// On exit, clean up and return success (0x0)
	delete scene;
	return 0;

	//glutInit(&argc, argv);          // Initialise GL environment
	//setup();                        // Call additional initialisation commands
	//glutDisplayFunc(draw);         // Register scene to render contents of draw() function
	//checkGLError();                 // Check any OpenGL errors in initialisation
	//glutReshapeFunc(reshape);

	//glEnable(GL_DEPTH_TEST);		// Enable depth testing for z-culling
	//glDepthFunc(GL_LEQUAL);			// Set the type of depth-test
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glutMainLoop();                 // Begin rendering sequence
	//return 0;
}
