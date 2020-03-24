#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	initialColor = glm::vec3(1, 0, 1);
	currentColor = initialColor;
	collision = false;
}

BoxCollider::BoxCollider(float side, glm::vec3 pos)
{
	initialColor = glm::vec3(1, 0, 1);
	currentColor = initialColor;
	colSide = side;
	position = pos;
	collision = false;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::checkCollision()
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

#include <iostream>
bool BoxCollider::CollideCheck(BoxCollider& other, ColisionData& objData)
{
	float min1x = position.x - (colSide / 2);
	float max1x = position.x + (colSide / 2);
	float min1y = position.y - (colSide / 2);
	float max1y = position.y + (colSide / 2);

	float min2x = other.position.x - (other.colSide / 2);
	float max2x = other.position.x + (other.colSide / 2);
	float min2y = other.position.y - (other.colSide / 2);
	float max2y = other.position.y + (other.colSide / 2);

	if ((min1x <= max2x && max2x >= min2x) && (min1y <= max2y && max1y >= min2y))
	{
		objData.depth=0;
		std::cout << "HIT" << std::endl;
		objData.normal = glm::normalize(position - other.position);

		objData.point = glm::vec3();

		return true;
	}
	else
	{
		return false;
	}
}

void BoxCollider::ChangePosition(glm::vec3 newPos)
{
	position = newPos;
}

void BoxCollider::Draw()
{
	checkCollision();
	glPushMatrix();
	glColor3f(currentColor.x, currentColor.y, currentColor.z);
	glTranslatef(position.x, position.y, position.z);
	glutWireCube(colSide);
	glPopMatrix();
}
