#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

//#include <iostream>
#include <vector>

#pragma comment(lib, "glew32.lib") 

#include "Cube.h"
#include "Particle.h"
#include "main.h"
#include "Player.h"
#include "RigidBody2D.h"

#include "SphereCollider.h"

class GameEngine
{
private:
	static std::vector<GameObject*> objects;
	static int oldTimeSinceStart;
	static int newTimeSinceStart;

	static void UpdateGame(void);
	static void DrawGame(void);
	static void CleanupEngine(void);
	static void ResizeWindow(int w, int h);

public:
	void InitEngine(int argc, char** argv, const char* windowTitle, int width, int height);
	void AddGameObject(GameObject*);
	void StartEngine(void);
};

