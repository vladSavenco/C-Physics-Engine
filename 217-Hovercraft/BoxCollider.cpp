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
		if ((min2x<min1x && min1x<max2x) &&(max2y>max1y && max1y>min2y))
		{
			float a1 = max1x - min2x;
			float a2 = max1y - min2y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2));
		}

		else if ((min2x>min1x && min1x>max2x)&&(min2y<min1y&&min1y<max2y))
		{
			float a1 = max2x - min1x;
			float a2 = max2y - min1y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2));
		}

		else if ((max2x>max1x && max1x>min2x)&&(max2y>max1y && max1y>min2y))
		{
			float a1 = max1x - min2x;
			float a2 = max1y - min2y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2));
		}

		else if ((max1x>min2x && max1x<max2x)&&(max2y>min1y && min1y>min2y))
		{
			float a1 = max1x-min2x;
			float a2 = max2y - min1y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2));
		}
		
		objData.normal = glm::normalize(position - other.position);

		//objData.point = glm::vec3();

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
