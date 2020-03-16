#pragma once

#include<iostream>
#include<vector>

#include <gtc\matrix_transform.hpp>

#include "Texture.h"
#include "Primitives.h"
#include "Material.h"
#include "Vertex.h"
#include "Shader.h"

class Mesh
{
private:
	unsigned nrOfVertices;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void initVAO(Primitives* primitive);

	void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies);

	void updateUniforms(Shader* shader);

	void updateModelMatrix();

public:
	Mesh(Primitives* primitive,
		glm::vec3 position,
		glm::vec3 rotation,
		glm::vec3 scale);

	Mesh(Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndicies,
		glm::vec3 position,
		glm::vec3 rotation,
		glm::vec3 scale);

	~Mesh();

	//Access Functions

	//Modifiers
	void setPosition(const glm::vec3& position);

	void setRotation(const glm::vec3& rotation);

	void setScale(const glm::vec3 setScale);

	//Functions
	void move(const glm::vec3 position);

	void rotate(const glm::vec3 rotation);

	void scaleUp(const glm::vec3 scale);

	void update();

	void render(Shader* shader);

};

