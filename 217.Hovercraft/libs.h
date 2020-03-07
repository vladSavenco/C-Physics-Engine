#pragma once

#include <vector>
#include <gtc\matrix_transform.hpp>

#include <SOIL2.h>

#include "Texture.h"
#include "Material.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};