#pragma once

#include "GameObject.h"

#include "SphereCollider.h"



class Player : public GameObject
{
private:
	float mass;

	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 totalForce;

	SphereCollider* SpC;

public:
	 Player(float mass, glm::vec3 pos);
	 ~Player();

	void Draw();
	void CalculateForces();
	void Update(float);
};

