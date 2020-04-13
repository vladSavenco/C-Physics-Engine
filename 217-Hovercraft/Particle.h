#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
private:
public:

	glm::vec3 acceleration;
	glm::vec3 totalForce;

	std::string colType;

	Particle(float mas, glm::vec3 pos,std::string cType);
	~Particle();

	void CalculateForces();

	void Draw();
	void Update(float);
};