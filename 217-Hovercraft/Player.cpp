#include "Player.h"



Player::Player(float mass, glm::vec3 pos) : GameObject(pos)
{
	this->mass = mass;

	velocity = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
}

Player::~Player()
{
}

void Player::Draw()
{
	glPushMatrix();
	glColor3f(1.f, 0.f, 1.0f);
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(0.5f, 10, 10);
	glPopMatrix();
}

void Player::CalculateForces()
{
}

void Player::Update(float deltaTime)
{
	totalForce = glm::vec3(0, 0, 0);

	if (GameObject::specialKeys[GLUT_KEY_UP])
	{
		totalForce += glm::vec3(0, 1, 0);
	}
	if (GameObject::specialKeys[GLUT_KEY_DOWN])
	{
		totalForce += glm::vec3(0, -1, 0);
	}
	if (GameObject::specialKeys[GLUT_KEY_RIGHT])
	{
		totalForce += glm::vec3(-1, 0,0);
	}
	if (GameObject::specialKeys[GLUT_KEY_LEFT])
	{
		totalForce += glm::vec3(1, 0,0);
	}

	glm::vec3 newVelocity;
	glm::vec3 newPosition;

	acceleration = totalForce / mass;
	newVelocity = velocity + acceleration * deltaTime;
	newPosition = position + velocity * deltaTime;

	velocity = newVelocity;
	position = newPosition;

	velocity *= pow(0.5, deltaTime);
}
