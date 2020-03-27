#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

GameObject::GameObject()
{
}

GameObject::GameObject(glm::vec3 pos,float mas)
{
	position = pos;
	velocity = glm::vec3(0,0,0);
	mass = mas;

	SpC.position = pos;
	SpC.radius = 1.0f;
	SpC.initialColor = glm::vec3(1.0f, 0.0f, 1.0f);

	//BoC.position = pos;
	//BoC.colSide = 1.0f;
	//BoC.initialColor = glm::vec3(1.0f, 0.0f, 1.0f);
}


GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

