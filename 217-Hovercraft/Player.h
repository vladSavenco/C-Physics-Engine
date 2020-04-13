#pragma once

#include "GameObject.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

class Player : public GameObject
{
private:
public:
	glm::vec3 acceleration;
	glm::vec3 totalForce;

	float inertia;
	glm::vec3 angularAcceleration;
	glm::vec3 angularVelocity;
	float orientation;
	glm::vec3 RotationTotalForce;

	std::string colType;

	 Player(float mass, glm::vec3 pos, std::string cType);
	 ~Player();

	void Draw();
	void CalculateForces();
	void Update(float);
};

