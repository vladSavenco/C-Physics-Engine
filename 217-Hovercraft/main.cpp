#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#pragma comment(lib, "glew32.lib") 

#include "Cube.h"
#include "Particle.h"
#include "main.h"

//Time Global Values
float oldTimeSinceStart, newTimeSinceStart;

//Object Vector
std::vector<GameObject*> objects;

//Creating Objects, cubes in this example
GameObject* cube = new Cube(glm::vec3(1, 1, 0));
GameObject* cube2 = new Cube(glm::vec3(3, 0, 1));

//Creating particles
GameObject* particle = new Particle(1.0f, glm::vec3(0, 0, 0));

// Drawing routine.
void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Position the objects for viewing.
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Draw();
	}

	glPushMatrix();
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(5, 0, 5);
	glVertex3f(-5, 0, 5);
	glVertex3f(-5, 0, -5);
	glVertex3f(5, 0, -5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.55, 0.27, 0.07);
	glRotatef(-45, 1, 0, 0);
	glutSolidCone(0.5, 0.75, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(-2, 0, 2);
	glTranslatef(-2, 0, 2);
	glRotatef(-90, 0, 1, 0);
	glutSolidCone(0.5, 0.75, 30, 30);
	glPushMatrix();
	glTranslatef(0, 0, -0.4);
	glColor3f(1, 1, 1);
	glutSolidCube(0.8);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Adding objects to the vector
	objects.push_back(cube);
	objects.push_back(cube2);

	objects.push_back(particle);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	GameObject::keys[key] = true;
	std::cout << "Key pressed: " << key << " : " << GameObject::keys[key] << std::endl;
	//If we press escape, quit
	if (key == 27)
		exit(0);
}

void keyInputUp(unsigned char key, int x, int y)
{
	GameObject::keys[key] = false;
	std::cout << "Key pressed: " << key << " : " << GameObject::keys[key] << std::endl;
}

void keySpecialInput(int key, int x, int y)
{
	GameObject::specialKeys[key] = true;
	std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
	//If we press escape, quit
	if (key == 4)
		exit(0);
}

void keySpecialInputUp(int key, int x, int y)
{
	GameObject::specialKeys[key] = false;
	std::cout << "Key pressed: " << key << " : " << GameObject::specialKeys[key] << std::endl;
}

void idle()
{
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	//std::cout << " --------------------------- " << std::endl;
	//std::cout << "OldTimeSinceStart: " << oldTimeSinceStart << std::endl;
	//std::cout << "NewTimeSinceStart: " << newTimeSinceStart << std::endl;

	float deltaTime = (newTimeSinceStart - oldTimeSinceStart);
	//std::cout << "Delta Time (ms): " << deltaTime << std::endl;
	deltaTime /= 1000.f;
	//std::cout << "Delta Time (seconds): " << deltaTime << std::endl;
	//std::cout << " --------------------------- " << std::endl;

	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(deltaTime);
	}

	glutPostRedisplay();
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(2, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Week 1 - Basic Scene");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);

	glutKeyboardFunc(keyInput);
	glutKeyboardUpFunc(keyInputUp);

	glutSpecialFunc(keySpecialInput);
	glutSpecialUpFunc(keySpecialInputUp);

	glutIdleFunc(idle);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
