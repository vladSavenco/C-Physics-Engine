#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

//#include <iostream>
#include <vector>

#pragma comment(lib, "glew32.lib") 

class SphereCollider
{
private:
	float radius;
	glm::vec3 position;

public:
	SphereCollider(float rad, glm::vec3 pos);
	~SphereCollider();

	bool CollideCheck(SphereCollider& other);

	void ChangePosition(glm::vec3 newPos);

	void Draw();
	void Update();
};

