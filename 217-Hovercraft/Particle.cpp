#include "Particle.h"

Particle::Particle(float m, glm::vec3 pos) : GameObject(pos)
{
	mass = m;
	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
}

Particle::~Particle()
{
}

void Particle::Draw()
{
	glPushMatrix();
	glColor3f(0.f, 1.f, 0.f);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();
}

void Particle::CalculateForces()
{
	totalForce = glm::vec3(0, 0, 0);
	totalForce += glm::vec3(0, -9.8f, 0) * mass;
}

void Particle::Update(float deltaTime)
{
	glm::vec3 newVelocity;
	glm::vec3 newPosition;

	CalculateForces();

	acceleration = totalForce / mass;
	newVelocity = velocity + acceleration * deltaTime;
	newPosition = position + velocity * deltaTime;

	velocity = newVelocity;
	position = newPosition;

}