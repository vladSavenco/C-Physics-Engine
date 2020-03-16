#include "Mesh.h"

void Mesh::initVAO(Primitives* primitive)
{
    //Set variables
    this->nrOfVertices = primitive->getNrOfVertices();
    this->nrOfIndices = primitive->getNrOfIndices();

    //Create VAO
    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    //GEN VAO And BIND and SEND DATA
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW);

    //GEN EBO and BIND and SEND DATA
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);

    //Set vertexAttribPointers and enable (input assembly)
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //Texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);
    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    //Bind VAO 0
    glBindVertexArray(0);
}

//Private
void Mesh::initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices)
{
    //Set variables
    this->nrOfVertices = nrOfVertices;
    this->nrOfIndices = nrOfIndices;

    //Create VAO
    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    //GEN VAO And BIND and SEND DATA
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices *sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

    //GEN EBO and BIND and SEND DATA
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices *sizeof(GLuint), indexArray, GL_STATIC_DRAW);

    //Set vertexAttribPointers and enable (input assembly)
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //Texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);
    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    //Bind VAO 0
    glBindVertexArray(0);
}

void Mesh::updateUniforms(Shader* shader)
{
    shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::updateModelMatrix()
{
    this->ModelMatrix = glm::mat4(1.f);
    this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
    this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
    this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

Mesh::Mesh(Primitives* primitive,
    glm::vec3 position,
    glm::vec3 rotation,
    glm::vec3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

    this->initVAO(primitive);
    this->updateModelMatrix();
}

//Public
Mesh::Mesh(Vertex* vertexArray,
    const unsigned& nrOfVertices, 
    GLuint* indexArray, 
    const unsigned& nrOfIndicies,
    glm::vec3 position = glm::vec3(0.f),
    glm::vec3 rotation = glm::vec3(0.f),
    glm::vec3 scale = glm::vec3(1.f))
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;

	this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndicies);
	this->updateModelMatrix();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

//Modifiers
void Mesh::setPosition(const glm::vec3& position)
{
    this->position = position;
}

void Mesh::setRotation(const glm::vec3& rotation)
{
    this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 setScale)
{
    this->scale = scale;
}

//Move
void Mesh::move(const glm::vec3 position)
{
    this->position += position;
}

void Mesh::rotate(const glm::vec3 rotation)
{
    this->rotation += rotation;
}

void Mesh::scaleUp(const glm::vec3 scale)
{
    this->scale += scale;
}

void Mesh::update()
{

}

void Mesh::render(Shader* shader)
{
    //Update uniforms
    this->updateModelMatrix();
    this->updateUniforms(shader);

    shader->use();

    ////Bind VAO
    glBindVertexArray(this->VAO);

    //Render
    /*if(this->indices.empty())
        glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    else*/
    glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
}
