#ifndef ___MyScene__
#define ___MyScene__

#ifdef __APPLE__                        // if OS X
#include <glut/glut.h>                  // include freeglut libraries
#else                                   // if Windows
#include <gl/glut.h>                    // include freeglut libraries
#endif

int width = 0;
int height = 0;

float xRot = 0.f;
float xRotSpeed = 0.25f;

#include <stdio.h>
#include <cmath>

void setup();
void draw();
void draw2();
void subdivide(int n, int r, GLdouble* a, GLdouble* b, GLdouble* c);
void reshape(int _width, int _height);
int main(int argc, char **argv);
void checkGLError();                        // Prints any OpenGL errors to console

#endif