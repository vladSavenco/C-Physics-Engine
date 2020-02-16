#pragma once

#include "GameObject.h"

class Player : public GameObject
{
private:
	float mass;

	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 totalForce;

public:
	 Player(float mass, glm::vec3 pos);
	 ~Player();

	void Draw();
	void CalculateForces();
	void Update(float);
};

