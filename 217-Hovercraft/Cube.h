#pragma once

#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube();
	Cube(glm::vec3 pos);
	~Cube();

	void Draw();
	void Update(float);
};
