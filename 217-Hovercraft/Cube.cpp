#include "Cube.h"

Cube::Cube()
{

}

Cube::Cube(glm::vec3 pos) : GameObject(pos)
{
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glColor3f(0,1,1);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void Cube::Update(float deltaTime)
{
	if (GameObject::specialKeys[GLUT_KEY_UP] == true)
		position.y += 1.f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_DOWN] == true)
		position.y -= 1.f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_LEFT] == true)
		position.x += 1.f * deltaTime;
	if (GameObject::specialKeys[GLUT_KEY_RIGHT] == true)
		position.x -= 1.f * deltaTime;
}
