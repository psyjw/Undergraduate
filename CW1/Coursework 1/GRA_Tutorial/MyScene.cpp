#include "MyScene.h"

void setup()
{
	width = 600;                                    // initialise global window variables
	height = 400;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("CW1");                        // create and show window (named CW1)
}

void draw()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);                   // set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
	glLoadIdentity();                                   // reset drawing

	glTranslatef(0.f, -5.f, -50.f);                     // move drawing further back in the scene
	glRotatef(xRot, 1.f, 1.f, 0.f);
	xRot += xRotSpeed;
	float r = 10.f;

	//regular tetrahedron
	//red
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, r, r);
	glVertex3f(r, 0.f, r);
	glVertex3f(r, r, 0);
	glEnd();

	//yellow
	glColor3f(1.f, 1.f, 0.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0, 0);
	glVertex3f(r, 0.f, r);
	glVertex3f(0.f, r, r);
	glEnd();

	//green
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0, 0);
	glVertex3f(r, r, 0.f);
	glVertex3f(r, 0.f, r);
	glEnd();

	//blue
	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.f, 0, 0);
	glVertex3f(0.f, r, r);
	glVertex3f(r, r, 0);
	glEnd();


	//draw the cube with transparent grey
	glColor4f(0.1f, 0.1f, 0.1f, 0.3f);
	//bottom triangle 1
	glBegin(GL_TRIANGLES);
	glNormal3d(0, -1, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(r, 0.f, 0.f);
	glVertex3f(r, 0.f, r);
	glEnd();
	//bottom triangle 2
	glBegin(GL_TRIANGLES);
	glNormal3d(0, -1, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(r, 0.f, r);
	glVertex3f(0.f, 0.f, r);
	glEnd();
	//front 1
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 1);
	glVertex3f(0.f, r, r);
	glVertex3f(r, 0.f, r);
	glVertex3f(r, r, r);
	glEnd();
	//front 2
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 1);
	glVertex3f(0.f, r, r);
	glVertex3f(0.f, 0.f, r);
	glVertex3f(r, 0.f, r);
	glEnd();
	//top 1
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 1, 0);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(r, r, r);
	glVertex3f(r, r, 0.f);
	glEnd();
	//top 2
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 1, 0);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(0.f, r, r);
	glVertex3f(r, r, r);
	glEnd();
	//back 1
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(r, r, 0.f);
	glVertex3f(r, 0.f, 0.f);
	glEnd();
	//back 2
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(r, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();
	//right 1
	glBegin(GL_TRIANGLES);
	glNormal3d(1, 0, 0);
	glVertex3f(r, r, r);
	glVertex3f(r, 0.f, 0.f);
	glVertex3f(r, r, 0.f);
	glEnd();
	//right 2
	glBegin(GL_TRIANGLES);
	glNormal3d(1, 0, 0);
	glVertex3f(r, r, r);
	glVertex3f(r, 0.f, r);
	glVertex3f(r, 0.f, 0.f);
	glEnd();
	//left 1
	glBegin(GL_TRIANGLES);
	glNormal3d(-1, 0, 0);
	glVertex3f(0.f, r, r);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();
	//left 2
	glBegin(GL_TRIANGLES);
	glNormal3d(-1, 0, 0);
	glVertex3f(0.f, r, r);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, r);
	glEnd();

	//draw outlines of the cube (just for good look)
	glColor3f(0.f, 0.f, 0.f);
	//bottom triangle 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(r, 0.f, 0.f);
	glVertex3f(r, 0.f, r);
	glEnd();
	//bottom triangle 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(r, 0.f, r);
	glVertex3f(0.f, 0.f, r);
	glEnd();
	//top 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(r, r, r);
	glVertex3f(r, r, 0.f);
	glEnd();
	//top 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(0.f, r, r);
	glVertex3f(r, r, r);
	glEnd();
	//right 1
	glBegin(GL_LINE_LOOP);
	glNormal3d(1, 0, 0);
	glVertex3f(r, r, r);
	glVertex3f(r, 0.f, 0.f);
	glVertex3f(r, r, 0.f);
	glEnd();
	//right 2
	glBegin(GL_LINE_LOOP);
	glNormal3d(1, 0, 0);
	glVertex3f(r, r, r);
	glVertex3f(r, 0.f, r);
	glVertex3f(r, 0.f, 0.f);
	glEnd();
	//left 1
	glBegin(GL_LINE_LOOP);
	glNormal3d(-1, 0, 0);
	glVertex3f(0.f, r, r);
	glVertex3f(0.f, r, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glEnd();
	//left 2
	glBegin(GL_LINE_LOOP);
	glNormal3d(-1, 0, 0);
	glVertex3f(0.f, r, r);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, r);
	glEnd(); 

	checkGLError();
	glutSwapBuffers();                                  // execute all commands, swap buffers
	glutPostRedisplay();								// Update variables
}


void subdivide(int n, int r, GLdouble* a, GLdouble* b, GLdouble* c){
    if (n == 0) {
        glBegin(GL_LINE_LOOP);
        glVertex3f(a[0], a[1], a[2]);
        glVertex3f(b[0], b[1], b[2]);
        glVertex3f(c[0], c[1], c[2]);
        glEnd();
        return;
    }

	GLdouble dist_to_centre = pow(r, 2);
    
    GLdouble* d = (GLdouble*) malloc(sizeof(GLdouble) * 3);
    GLdouble* e = (GLdouble*) malloc(sizeof(GLdouble) * 3);
    GLdouble* f = (GLdouble*) malloc(sizeof(GLdouble) * 3);
    
    for (int i = 0; i < 3; i++) {
        d[i] = a[i] + b[i];
        e[i] = b[i] + c[i];
        f[i] = a[i] + c[i];
    }
    
    GLdouble delta_d = sqrt(dist_to_centre / (pow(d[0], 2) + pow(d[1], 2) + pow(d[2], 2)));
    GLdouble delta_e = sqrt(dist_to_centre / (pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2)));
    GLdouble delta_f = sqrt(dist_to_centre / (pow(f[0], 2) + pow(f[1], 2) + pow(f[2], 2)));
    
    for (int i = 0; i < 3; i++) {
        d[i] = d[i] * delta_d;
        e[i] = e[i] * delta_e;
        f[i] = f[i] * delta_f;
    }
    
    subdivide(n - 1, r, a, d, f);
    subdivide(n - 1, r, d, b, e);
    subdivide(n - 1, r, f, e, c);
    subdivide(n - 1, r, d, e, f);
}

void draw2()
{
    glClearColor(1.f, 1.f, 1.f, 1.f);                   // set background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
    glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
    glLoadIdentity();                                   // reset drawing
    
    glTranslatef(0.f, 0.f, -300.f);                     // move drawing further back in the scene
    glColor3f(0.f, 0.f, 0.f);                           // set draw colour to black

    int n = 3;
    double radius = 100.f;
    GLdouble a[3] = {0.f, radius, 0.f};
    GLdouble b[3] = {0.f, 0.f, radius};
    GLdouble c[3] = {-radius, 0.f, 0.f};
    GLdouble d[3] = {0.f, 0.f, -radius};
    GLdouble e[3] = {radius, 0.f, 0.f};
    GLdouble f[3] = {0.f, -radius, 0.f};

    subdivide(n, radius, a, b, c);
    subdivide(n, radius, a, c, d);
    subdivide(n, radius, a, d, e);
    subdivide(n, radius, a, e, b);
    subdivide(n, radius, f, b, c);
    subdivide(n, radius, f, c, d);
    subdivide(n, radius, f, d, e);
    subdivide(n, radius, f, e, b);
    
    checkGLError();
    glutSwapBuffers();                                  // execute all commands, swap buffers
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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // Initialise GL environment
	setup();                        // Call additional initialisation commands
	glutDisplayFunc(draw);         // Register scene to render contents of draw() function
	checkGLError();                 // Check any OpenGL errors in initialisation
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);		// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);			// Set the type of depth-test
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();                 // Begin rendering sequence
	return 0;
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
