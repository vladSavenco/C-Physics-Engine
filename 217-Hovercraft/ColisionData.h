#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>


class GameObject;

struct ColisionData
{
	glm::vec3 normal;
	glm::vec3 point;
	float depth=0;
	GameObject* obj1;
	GameObject* obj2;
};

