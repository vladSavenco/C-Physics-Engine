#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <map>
#include "SphereCollider.h"
#include "BoxCollider.h"

#include <iostream>

class GameObject
{

protected:


public:
	glm::vec3 position;
	glm::vec3 velocity;
	float mass;
	std::string colType;

	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;;

	SphereCollider SpC;
	BoxCollider BoC;

	GameObject();
	GameObject(glm::vec3 pos,float mas,std::string cType);
	~GameObject();

	virtual void Draw()=0;

	virtual void Update(float);
};
