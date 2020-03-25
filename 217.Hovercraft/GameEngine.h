#pragma once

#include "libs.h"
#include "ObjectLoader.h"

//Enumerations, for each element. Need to be declared before they are created in the cpp file
enum shader_enum
{
	SHADER_CORE_PROGRAM = 0
};

enum texture_enum
{
	TEX_PANZER,TEX_PANZER_SPECULAR, TEX_GEORGE, TEX_GEORGE_SPECULAR
	, TEX_SKYBOX, TEX_SKYBOX_SPECULAR
	, TEX_GRASS, TEX_GRASS_SPECULAR
};

enum material_enum
{
	MAT_1=0
};

enum mesh_enum
{
	MESH_QUAD = 0
};

class GameEngine
{
private:
	//Variables---
	//Window
	GLFWwindow* window;
	const int Window_Width, window_Height;
	int frameBufferWidth, frameBufferHeight;
	//OpenGl Context
	const int GL_Version_Major, GL_Version_Minor;

	//Funtions Private
	void initGLFW();
	void initWindow(const char* title, bool resizable);

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders vector to hold the shaders
	std::vector<Shader*> shaders;

	//Textures vector for storing textures
	std::vector<Texture*> textures;

	//Materiala vector for storing materials
	std::vector<Material*> materials;

	//Models vector for storing models
	std::vector<Model*> models;

	//Lights vector to hold the lights
	std::vector<glm::vec3*> lights;

	//After window is created otherwise it will not work.
	void initGLEW();
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();
	void initObjFromFile();
	void initModels();
	void initLights();
	void initUniforms();
	void updateUniforms();

public:
	GameEngine(const char* title, const int Window_Width, const int Window_Height, const int GL_Version_Major, const int GL_Version_Minor, bool resizable);
	virtual ~GameEngine();

	//Accessors
	int GetWindowShouldClose();

	//Modifiers
	void setWindowShouldClose();

	//Functions
	void update();
	void render();

	//Static Functions
	static void frameBuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};

