#include "../Interface/Animation.h"
#include "../Interface/Input.h"
#include "Scene.h"
#include "../Interface/DisplayableObject.h"
#include <cstdlib>

Texture Scene::texture = Texture();		// Initialise Texture handler
Camera Scene::camera = Camera();        // Initialise Camera object
int status = 0;
bool moving[4] = { 0 };
bool shooting[4] = { 0 };

Scene::Scene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Engine(argc, argv, title, windowWidth, windowHeight)
{
	camera.Reset(); // Set Camera to default properties
}
/**
 * Destructor: deletes all {@link DisplayableObject}s in the Scene
 */
Scene::~Scene()
{
	for (DisplayableObject* obj : objects)
	{
		if (obj != NULL)
			delete obj;
		obj = NULL;
	}
}

int Scene::GetWindowWidth()
{
	return Engine::windowWidth;
}

int Scene::GetWindowHeight()
{
	return Engine::windowHeight;
}

int Scene::GetTexture(std::string filename)
{
	return texture.GetTexture(filename);
}

void Scene::Initialise()
{
	// Override in your class
}

void Scene::Draw()
{
	// Clear colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Update based on window details (also sets initial projection properties)
	Reshape(windowWidth, windowHeight);
	// Reset MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Setup viewing properties
	camera.SetupCamera();
	// Display all objects in the Scene

	
	for (DisplayableObject* obj : objects) {
		if (firstObj == true) {
			glEnable(GL_CULL_FACE);
			obj->Display();
			firstObj = false;
			glDisable(GL_CULL_FACE);
		}
		else {		
			obj->Display();
		}	
	}
	firstObj = true;

	//set stencil value; when drawing mirror, set reflection area stencil value to be 1
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//Disable writting into the depth buffer, otherwise the buffer will be updated and the reflection cannot be drawn
	glDepthMask(GL_FALSE);
	DrawMirror();
	glDepthMask(GL_TRUE);

	//set stencil test, value not equal to the stencil value of mirror will not be drawn
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilFunc(GL_KEEP, GL_KEEP, GL_REPLACE);

	//draw the reflection
	glPushMatrix();
	glScalef(1.0,-1.0,1.0);

	for (DisplayableObject* obj : objects) {
		if (firstObj == true) {
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CW);
			glPushMatrix();
			glScalef(0.99f, 0.99f, 0.99f);
			obj->Display();
			glPopMatrix();
			firstObj = false;
			glDisable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
		}
		else {
			obj->Display();
		}
	}
	firstObj = true;

	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	// Zealous reset of MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Dump silent GL errors into console output
	CheckGLError();
}

void Scene::DrawMirror() {
	glPushMatrix();                                         // save transformation state
	glPushAttrib(GL_ALL_ATTRIB_BITS);                   // save style attributes (and more)
	glEnable(GL_CULL_FACE);

	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(15, 0, -15);
	glVertex3f(-15, 0, -15);
	glVertex3f(-15, 0, 15);
	glVertex3f(15, 0, 15);
	glEnd();

	glPopAttrib();                                      // restore style attributes
	glPopMatrix();                                          // restore transformation state
}

void Scene::Reshape(int w, int h)
{
	// update window properties
	windowWidth = w;
	windowHeight = h;
	// Reset projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Generate new projection transform based on updated window properties
	Projection();
	// Revert to MODELVIEW (for viewing)
	glMatrixMode(GL_MODELVIEW);
	// Update viewport for new window dimensions
	camera.SetViewport();
}

void Scene::Projection(){
	// Default orthographic projection
	glOrtho(static_cast<GLdouble>(-windowWidth) / static_cast<GLdouble>(2.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(2.0),
			static_cast<GLdouble>(-windowHeight) / static_cast<GLdouble>(2.0), static_cast<GLdouble>(windowHeight) / static_cast<GLdouble>(2.0),
			static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}

void Scene::Update(const double& deltaTime)
{
	Animation* animated_obj;
	// Update camera/view
	camera.Update(deltaTime);
	// Iterate through objects to update animations
	for (DisplayableObject* obj : objects)
	{
		animated_obj = dynamic_cast<Animation*>(obj); // Cast to animation
		if (animated_obj != NULL) // If cast successful
			animated_obj->Update(deltaTime); // Call update sequence for obj
	}
}

void Scene::AddObjectToScene(DisplayableObject* obj){
	objects.push_back(obj); // Object added to list (vector) of those to display in Scene
}

void Scene::HandleKey(unsigned char key, int state, int x, int y)
{
	// Handle Keyboard input (ASCII) and pass to objects.
	// State is 1 for key press, 0 for key release

	if (key == 27 && state) // Check for escape key pressed
	{
		exit(0); // EXIT ON ESCAPE PRESS
	}

	Input* input_obj;
	camera.HandleKey(key, state, x, y);
	for (DisplayableObject* obj : objects)
	{
		input_obj = dynamic_cast<Input*>(obj);
		if (input_obj != NULL)
			input_obj->HandleKey(key, state, x, y);
	}
}

void Scene::HandleSpecialKey(int key, int state, int x, int y)
{
	// Handle Special Keyboard input (non-ASCII) and pass to objects.
	// State is 1 for key press, 0 for key release
	Input* input_obj;
	camera.HandleSpecialKey(key, state, x, y);
	for (DisplayableObject* obj : objects)
	{
		input_obj = dynamic_cast<Input*>(obj);
		if (input_obj != NULL)
			input_obj->HandleSpecialKey(key, state, x, y);
	}
}

void Scene::HandleMouse(int button, int state, int x, int y)
{
	// Handle mouse input and pass to objects.
	// State is 1 for button press, 0 for key release
	Input* input_obj;
	camera.HandleMouse(button, state, x, y);
	for (DisplayableObject* obj : objects)
	{
		input_obj = dynamic_cast<Input*>(obj);
		if (input_obj != NULL)
			input_obj->HandleMouse(button, state, x, y);
	}
}

void Scene::HandleMouseDrag(int x, int y)
{
	// Handle mouse movement while button is pressed (active motion)
	Input* input_obj;
	camera.HandleMouseDrag(x, y);
	for (DisplayableObject* obj : objects)
	{
		input_obj = dynamic_cast<Input*>(obj);
		if (input_obj != NULL)
			input_obj->HandleMouseDrag(x, y);
	}
}

void Scene::HandleMouseMove(int x, int y)
{
	// Handle passive mouse movement, called whether button is pressed or not
	Input* input_obj;
	camera.HandleMouseMove(x, y);
	for (DisplayableObject* obj : objects)
	{
		input_obj = dynamic_cast<Input*>(obj);
		if (input_obj != NULL)
			input_obj->HandleMouseMove(x, y);
	}
}
