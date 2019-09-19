#pragma once

#include "../Framework/Engine/Scene.h"
#include "Suppressor.h"
#include "Stock.h"
#include "Magazine.h"
#include "Scope.h"
#include "Body.h"
#include "Bolt.h"
#include "Trigger.h"
#include "Bullet.h"
#include "Shell.h"
#include "Skybox.h"
#include "Light.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};

private:
	void Initialise();
	void Projection();

	GLint texID;
};