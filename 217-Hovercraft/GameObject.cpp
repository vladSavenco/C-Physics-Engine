#include "GameObject.h"

std::map<char, bool> GameObject::keys;
std::map<int, bool> GameObject::specialKeys;

GameObject::GameObject()
{
}

GameObject::GameObject(glm::vec3 pos)
{
	position = pos;

	SpC = new SphereCollider(1.f, pos);
}


GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

