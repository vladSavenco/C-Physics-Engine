#pragma once
#include <iostream>
#include "GameObject.h"

class RigidBody2D : public GameObject
{
private:
	float mass;
	glm::vec3 position;
	glm::vec3 acceleration;
	glm::vec3 velocity;
	glm::vec3 linearTotalForce;

	float inertia;
	glm::vec3 angularAcceleration;
	glm::vec3 angularVelocity;
	float orientation;
	glm::vec3 RotationalTotalForce;
	//shape information ?

	float length;
	float width;

public:
	RigidBody2D(glm::vec3 position);
	~RigidBody2D();

	void Draw();

	void Update(float);
};

