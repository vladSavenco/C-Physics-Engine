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
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 originPos;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 ModelMatrix;

	void initVAO();

	void updateUniforms(Shader* shader);

	void updateModelMatrix();

public:
	Mesh(Primitives* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndicies, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	Mesh(const Mesh& obj);

	~Mesh();

	//Movement for initial placement
	void setOriginPos(const glm::vec3& originPos);

	void setPosition(const glm::vec3& position);

	void setRotation(const glm::vec3& rotation);

	void setScale(const glm::vec3 setScale);

	//Movement Functions - to be used with key presses
	void move(const glm::vec3 position);

	void rotate(const glm::vec3 rotation);

	void scaleUp(const glm::vec3 scale);

	//Update and Render
	void update();

	void render(Shader* shader);

};