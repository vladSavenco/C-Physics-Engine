#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

GameObject::GameObject()
{
}

GameObject::GameObject(glm::vec3 pos)
{
	position = pos;
	SpC.position = pos;
	SpC.radius = 1.0f;
	SpC.initialColor = glm::vec3(1.0f, 0.0f, 1.0f);
	//SpC = new SphereCollider(1.f, pos);
}


GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

