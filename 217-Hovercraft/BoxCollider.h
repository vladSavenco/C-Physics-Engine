#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

//#include <iostream>
#include <vector>
#include "ColisionData.h"
#include "SphereCollider.h"

#pragma comment(lib, "glew32.lib") 

class BoxCollider
{
public:
	float colSide;

	BoxCollider();
	BoxCollider(float side, glm::vec3 pos);

	glm::vec3 position;
	~BoxCollider();

	glm::vec3 initialColor;
	glm::vec3 currentColor;

	bool collision;

	void checkCollision();

	bool CollideCheck(BoxCollider& other, ColisionData& objData);

	bool CollideCheckSphere(SphereCollider& other, ColisionData& objData);

	void ChangePosition(glm::vec3 newPos);

	void Draw();
};

