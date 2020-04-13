#include "Player.h"

Player::Player(float mas, glm::vec3 pos,std::string cType) : GameObject(pos,mas,cType)
{
	acceleration = glm::vec3(0, 0, 0);
	totalForce = glm::vec3(0, 0, 0);
	inertia = 1.f / 6.f;
	orientation = 0.f;

	colType = cType;
}

Player::~Player()
{
}

void Player::Draw()
{
	glPushMatrix();
	glColor3f(0.35f, 0.46f, 0.84f);
	glTranslatef(position.x, position.y, position.z);
	glRotatef(orientation, 0, 0, 1);
	glutSolidCube(1.f);
	glPopMatrix();

	if (colType == "sphere")
	{
		SpC.Draw();
	}
	else if (colType == "box")
	{
		BoC.Draw();
	}
}

void Player::CalculateForces()
{
}

void Player::Update(float deltaTime)
{
	totalForce = glm::vec3(0, 0, 0);
	RotationTotalForce = glm::vec3(0, 0, 0);

	//Keyboard Input
	if (GameObject::specialKeys[GLUT_KEY_UP])
	{
		totalForce += glm::vec3(0, 5, 0);
	}
	if (GameObject::specialKeys[GLUT_KEY_DOWN])
	{
		totalForce += glm::vec3(0, -5, 0);
	}
	if (GameObject::specialKeys[GLUT_KEY_RIGHT])
	{
		RotationTotalForce += glm::cross(glm::vec3(1, 1, 0), glm::vec3(-50, 0, 0));
	}
	if (GameObject::specialKeys[GLUT_KEY_LEFT])
	{
		RotationTotalForce += glm::cross(glm::vec3(-1, 1, 0), glm::vec3(50, 0, 0));
	}

	auto rotatedVec=glm::rotate(totalForce, glm::radians(orientation), glm::vec3(0.f,0.f,1.f));

	totalForce = rotatedVec;

	glm::vec3 newVelocity;
	glm::vec3 newPosition;

	CalculateForces();

	acceleration = totalForce / mass;
	newVelocity = velocity + acceleration * deltaTime;
	newPosition = position + velocity * deltaTime;

	velocity = newVelocity;
	position = newPosition;

	if (colType == "sphere")
	{
		SpC.ChangePosition(newPosition);
	}
	else if (colType == "box")
	{
		BoC.ChangePosition(newPosition);
	}

	//Dampen
	velocity *= pow(0.5, deltaTime);

	//Angular
	glm::vec3 newAngVelocity;

	angularAcceleration = RotationTotalForce / inertia;
	newAngVelocity = angularVelocity + angularAcceleration * deltaTime;

	//std::cout << "VEL: " <<  glm::to_string(angularVelocity) << std::endl;
	float newOrientation = orientation + angularVelocity.z * deltaTime;

	angularVelocity = newAngVelocity;
	orientation = newOrientation;
	//std::cout << "ORI: " << orientation << std::endl;
	angularVelocity *= pow(0.1, deltaTime);
}
