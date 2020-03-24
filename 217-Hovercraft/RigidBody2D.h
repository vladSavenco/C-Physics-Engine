#pragma once
#include <iostream>
#include "GameObject.h"
#include <glm/gtx/string_cast.hpp>

class RigidBody2D : public GameObject
{
private:
	glm::vec3 position;
	glm::vec3 acceleration;
	glm::vec3 totalForce;

	float inertia;
	glm::vec3 angularAcceleration;
	glm::vec3 angularVelocity;
	float orientation;
	glm::vec3 RotationTotalForce;

	//shape information ?
	float length;
	float width;

	glm::vec3 force1;
	glm::vec3 force2;

public:
	RigidBody2D(float mas,float length,float width,glm::vec3 position);
	~RigidBody2D();

	void Draw();

	void CalculateForces();

	void Update(float);
};

