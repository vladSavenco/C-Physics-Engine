#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <map>

class GameObject
{

protected:
	glm::vec3 position;
public:

	static std::map<char, bool> keys;
	static std::map<int, bool> specialKeys;

	GameObject();
	GameObject(glm::vec3 pos);
	~GameObject();

	virtual void Draw()=0;

	virtual void Update(float);
};
