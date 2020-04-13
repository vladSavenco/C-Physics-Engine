#include "RigidBody2D.h"
#include <iostream>


RigidBody2D::RigidBody2D(float mas, float length, float width, glm::vec3 position,std::string cType) : GameObject(position,mas,cType)
{
	force1 = glm::vec3(1, 0, 0);
	force2 = glm::vec3(2, 0, 0);

	inertia = 1.0f / 6.0f;
	std::cout << "Inertia= " << inertia << std::endl;

	angularAcceleration =glm::vec3(0,0,0);
	angularVelocity = glm::vec3(0,0,0);
	orientation = 0.0f;

}

RigidBody2D::~RigidBody2D()
{
}

void RigidBody2D::Draw()
{
	glPushMatrix(); //dont affect other objects, only this one so take a copy of the matrix and put it on the stack
	glTranslatef(position.x, position.y, position.z);
	glRotatef(orientation, 0, 0, 1);
	glColor3f(1.f, 1.f, 1.f);

	glBegin(GL_QUADS);
	glVertex3f(-1, 1, 0); //top left
	glVertex3f(1, 1, 0); //top right
	glVertex3f(1, -1, 0); //bottom right
	glVertex3f(-1, -1, 0); //bottom left
	glEnd();

	glPointSize(5.0f);

	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_POINTS);
	//at the middle of object
	glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();
}

void RigidBody2D::CalculateForces()
{
	totalForce = glm::vec3(0, 0, 0);
	totalForce += force1;

	RotationTotalForce = glm::vec3(0, 0, 0);
	RotationTotalForce += glm::cross(glm::vec3(1,1,0), glm::vec3(1, 0, 0));

	std::cout << RotationTotalForce.x << " " << RotationTotalForce.y << " " << RotationTotalForce.z << std::endl;
}

void RigidBody2D::Update(float deltaTime)
{
	//Liniar
	glm::vec3 newVelocity;
	glm::vec3 newPosition;

	CalculateForces();

	acceleration = totalForce / mass;
	newVelocity = velocity + acceleration * deltaTime;
	newPosition = position + velocity * deltaTime;

	velocity = newVelocity;
	position = newPosition;

	//Dampen
	velocity *= pow(0.5, deltaTime);
	
	//Angular
	glm::vec3 newAngVelocity;
	//glm::vec3 newOrientation;

	angularAcceleration = RotationTotalForce / inertia;
	newAngVelocity = angularVelocity + angularAcceleration * deltaTime;

	std::cout << glm::to_string(angularVelocity) << std::endl;
	float newOrientation = orientation + angularVelocity.z * deltaTime;

	//std::cout << glm::to_string(newOrientation) << std::endl;
	angularVelocity = newAngVelocity;
	orientation = newOrientation;
}
