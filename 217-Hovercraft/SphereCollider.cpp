#include "SphereCollider.h"

SphereCollider::SphereCollider()
{
}

SphereCollider::SphereCollider(float rad, glm::vec3 pos)
{
	radius = rad;
	position = pos;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::checkCollision()
{
	if (collision)
	{
		currentColor = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		currentColor = initialColor;
	}
}

bool SphereCollider::CollideCheck(SphereCollider& other, ColisionData& objData)
{
	float distance = sqrt(pow(position.y-other.position.y,2)+pow(position.x-other.position.x,2)+pow(position.z - other.position.z, 2));
	float totalRadius = radius + other.radius;
	

	if (totalRadius >= distance)
	{
		objData.depth = totalRadius-distance;
		objData.normal =glm::normalize(position-other.position);
		objData.point = position*objData.normal*radius;
		
		return true;
		
	}
	else
	{
		return false;
	}
}

void SphereCollider::ChangePosition(glm::vec3 newPos)
{
	position = newPos;
}

void SphereCollider::Draw()
{
	checkCollision();
	glPushMatrix();
	glColor3f(currentColor.x,currentColor.y,currentColor.z);
	glTranslatef(position.x, position.y, position.z);
	glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

