#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
private:

	float mass;

	glm::vec3 acceleration;
	glm::vec3 velocity;
	//Particle already has position from GameObject!

	glm::vec3 totalForce;

public:
	Particle(float m, glm::vec3 pos);
	~Particle();

	void CalculateForces();

	void Draw();
	void Update(float);
};