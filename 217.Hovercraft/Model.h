#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

class Model
{
private:
	Material* material;
	Texture* TexDiffuse;
	Texture* TexSpecular;
	std::vector<Mesh*> meshes;
	glm::vec3 mainPosition;

	void updateUniforms();

public:
	Model(glm::vec3 mainPosition, Material* material, Texture* TexDiffuse, Texture* TexSpecular, std::vector<Mesh*>meshes);

	~Model();

	//movement Functions
	void rotate(const glm::vec3 rotation);

	//Rendering function
	void update();
	void render(Shader* shader);
};

