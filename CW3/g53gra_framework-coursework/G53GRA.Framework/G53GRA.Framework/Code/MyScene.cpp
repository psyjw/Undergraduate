#include "MyScene.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
}

void MyScene::Initialise()
{
	glDisable(GL_LIGHTING);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	texID = Scene::GetTexture("./Textures/body.bmp");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Skybox *skybox = new Skybox();
	skybox->position(0.f, 0.f, 0.f);
	skybox->size(100.0f, 100.0f, 100.0f);
	AddObjectToScene(skybox);
	Suppressor* suppressor = new Suppressor();
	suppressor->position(0.f, 9.75f, 0.f);
	AddObjectToScene(suppressor);
	Stock* stock = new Stock();
	stock->position(-16.f, 7.f, 0.f);
	AddObjectToScene(stock);
	Magazine* magazine = new Magazine();
	magazine->position(-1.f, 8.5f, 0.f);
	AddObjectToScene(magazine);
	Scope* scope = new Scope();
	scope->position(-7.5f, 10.5f, 0.f);
	AddObjectToScene(scope);
	Body* body = new Body(texID);
	body->position(0.f, 10.f, 0.f);
	AddObjectToScene(body);
	Bolt* bolt = new Bolt(texID);
	bolt->position(0.f, 10.f, 0.f);
	AddObjectToScene(bolt);
	Trigger* trigger = new Trigger();
	trigger->position(-7.f, 8.5f, 0.f);
	AddObjectToScene(trigger);
	Bullet* bullet = new Bullet();
	bullet->position(-2.f, 10.f, 0.f);
	AddObjectToScene(bullet);
	Shell* shell = new Shell();
	shell->position(-4.75f, 9.75f, 0.f);
	AddObjectToScene(shell);
	Light *light = new Light();
	light->position(0.0f, 0.0f, -90.0f);
	AddObjectToScene(light);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 6000.0);
}

