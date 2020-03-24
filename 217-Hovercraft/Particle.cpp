#include "Particle.h"

Particle::Particle(float mas, glm::vec3 pos) : GameObject(pos,mas)
{
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

	//SpC.Draw();
	BoC.Draw();
}

void Particle::CalculateForces()
{
	totalForce = glm::vec3(0, 0, 0);
	totalForce += glm::vec3(0, 0.f, 0) * mass; //9.8f instead of 0.f for gravity.
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

	//SpC.ChangePosition(newPosition);
	BoC.ChangePosition(newPosition);

	velocity *= pow(0.5, deltaTime);

}