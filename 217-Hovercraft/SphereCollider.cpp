#include "SphereCollider.h"

SphereCollider::SphereCollider(float rad, glm::vec3 pos)
{
	radius = rad;
	position = pos;
}

SphereCollider::~SphereCollider()
{
}

bool SphereCollider::CollideCheck(SphereCollider& other)
{
	float distance;
	float totalRadius;

	distance = sqrt(pow(position.y-other.position.y,2)+pow(position.x-other.position.x,2));
	totalRadius = radius + other.radius;

	if (radius >= distance)
		return true;
	else
		return false;
}

void SphereCollider::ChangePosition(glm::vec3 newPos)
{
	position = newPos;
}

void SphereCollider::Draw()
{
	glPushMatrix();
	glColor3f(1.f, 0.f, 1.0f); //Magenta is the best debug colour!
	glTranslatef(position.x, position.y, position.z);
	glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

void SphereCollider::Update()
{
}
