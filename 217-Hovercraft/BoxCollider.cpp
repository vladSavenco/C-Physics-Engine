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
		if ((min2x<=min1x && min1x<=max2x) &&(max2y>=max1y && max1y>=min2y))
		{
			float a1 = max1x - min2x;
			float a2 = max1y - min2y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2))/2;


			std::cout << "1" << std::endl;
		}

		else if ((min2x>min1x && min1x>max2x)&&(min2y<min1y&&min1y<max2y))
		{
			float a1 = max2x - min1x;
			float a2 = max2y - min1y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2))/2;

			std::cout << "2" << std::endl;
		}

		else if ((max2x>max1x && max1x>min2x)&&(max2y>max1y && max1y>min2y))
		{
			float a1 = max1x - min2x;
			float a2 = max1y - min2y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2))/2;

			std::cout << "3" << std::endl;
		}

		else if ((max1x>min2x && max1x<max2x)&&(max2y>min1y && min1y>min2y))
		{
			float a1 = max1x-min2x;
			float a2 = max2y - min1y;

			objData.depth = sqrt(pow(a1, 2) + pow(a2, 2))/2;

			std::cout << "4" << std::endl;
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

bool BoxCollider::CollideCheckSphere(SphereCollider& other, ColisionData& objData)
{

	float min1x = position.x - (colSide / 2);
	float max1x = position.x + (colSide / 2);
	float min1y = position.y - (colSide / 2);
	float max1y = position.y + (colSide / 2);

	float min2x = other.position.x - (other.radius);
	float max2x = other.position.x + (other.radius);
	float min2y = other.position.y - (other.radius);
	float max2y = other.position.y + (other.radius);

	//Sides

	if ((min2y>min1y&&min2y<max1y) && (other.position.x>min1x && other.position.x<max1x))
	{

		//std::cout << "hit" << std::endl;

		objData.depth =(max1y-min2y)/2;

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	else if ((max2y > min1y&& max2y < max1y) && (other.position.x > min1x&& other.position.x < max1x))
	{
		//std::cout << "hit" << std::endl;

		objData.depth = (max2y-min1y)/2;

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	else if ((max2x > min1x&& max2x < max1x) && (other.position.y > min1y&& other.position.y < max1y))
	{
		//std::cout << "hit" << std::endl;

		objData.depth = (max2x-min1x)/2;

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	else if ((min2x > min1x&& min2x < max1x) && (other.position.y > min1y&& other.position.y < max1y))
	{
		//std::cout << "hit" << std::endl;

		objData.depth = (max1x-min2x)/2;

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	//corners

	else if (sqrt(pow(other.position.x - max1x, 2) + pow(other.position.y - max1y, 2)) < other.radius)
	{
		//std::cout << "hit" << std::endl;

		objData.depth = other.radius - sqrt(pow(other.position.x - max1x, 2) + pow(other.position.y - max1y, 2));

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	else if (sqrt(pow(min1x-other.position.x, 2) + pow(other.position.y-max1y, 2)) < other.radius)
	{
		//std::cout << "hit" << std::endl;

		objData.depth = other.radius - sqrt(pow(min1x - other.position.x, 2) + pow(other.position.y - max1y, 2));

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	else if (sqrt(pow(min1x - other.position.x, 2) + pow(min1y-other.position.y, 2)) < other.radius)
	{
		//std::cout << "hit" << std::endl;

		objData.depth = other.radius - sqrt(pow(min1x - other.position.x, 2) + pow(min1y - other.position.y, 2));

		objData.normal = glm::normalize(position - other.position);

		return true;
	}

	else if (sqrt(pow(other.position.x-max1x, 2) + pow(max1y - other.position.y, 2)) < other.radius)
	{
		//std::cout << "hit" << std::endl;

		objData.depth = other.radius - sqrt(pow(other.position.x - max1x, 2) + pow(max1y - other.position.y, 2));

		objData.normal = glm::normalize(position - other.position);

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
