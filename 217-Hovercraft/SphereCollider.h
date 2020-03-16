#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

//#include <iostream>
#include <vector>
#include "ColisionData.h"

#pragma comment(lib, "glew32.lib") 

class SphereCollider
{
public:
	SphereCollider();
	SphereCollider(float rad, glm::vec3 pos);
	float radius;
	glm::vec3 position;
	~SphereCollider();

	glm::vec3 initialColor;
	glm::vec3 currentColor;

	bool collision;

	void checkCollision();

	bool CollideCheck(SphereCollider& other, ColisionData& objData);

	void ChangePosition(glm::vec3 newPos);

	void Draw();
};

