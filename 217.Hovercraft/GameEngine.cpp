#include "GameEngine.h"

//Funtions Private

//Initialise GLFW
void GameEngine::initGLFW()
{
    //Init GLFW
    glfwInit();
}

//Initialise the window
void GameEngine::initWindow(const char* title, bool resizable)
{
    //Creating the window 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_Version_Major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_Version_Minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    this->window = glfwCreateWindow(this->Window_Width,this->window_Height, title, NULL, NULL);

    glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
    glfwSetFramebufferSizeCallback(this->window, GameEngine::frameBuffer_resize_callback);

    //glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    //Important, needs to happen before loading GLEW.
    glfwMakeContextCurrent(this->window);
}

//Initialise GLEW
void GameEngine::initGLEW()
{
    glewExperimental = GL_TRUE;
    glewInit();
}

//Initialise OpenGLOptions
void GameEngine::initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//Initialise Matrices
void GameEngine::initMatrices()
{
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight, this->nearPlane, this->farPlane);
}

//Initialise Shaders
void GameEngine::initShaders()
{
    this->shaders.push_back(new Shader(this->GL_Version_Major, this->GL_Version_Minor, "vertex_core.glsl", "fragment_core.glsl"));
}

//Initialise Textures
void GameEngine::initTextures()
{
    //Texture 0
    this->textures.push_back(new Texture ("Images/panzer.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/panzerSpecular.jpg", GL_TEXTURE_2D));

    //Texture 1
    this->textures.push_back(new Texture("Images/george.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/georgeSpecular.jpg", GL_TEXTURE_2D));
}

//Initialise Materials
void GameEngine::initMaterials()
{
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f),0,1));
}

void GameEngine::initObjFromFile()
{
    //std::vector<Vertex>hoverCraft = objectLoader("ObjModels/Hovercraft.obj");
}

void GameEngine::initMeshes()
{
    std::vector<Vertex>hoverCraft = objectLoader("ObjModels/Hovercraft.obj");

    this->meshes.push_back(new Mesh(hoverCraft.data(),hoverCraft.size(),NULL,0, glm::vec3(0.f,0.f,2.f), glm::vec3(0.f), glm::vec3(1.f)));

    this->meshes.push_back(new Mesh(&Pyramid(), glm::vec3(2.f,0.f,0.f), glm::vec3(0.f), glm::vec3(1.f)));
}

//Initialise Lights in scene
void GameEngine::initLights()
{
    this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

//Initialise Uniforms
void GameEngine::initUniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void GameEngine::updateUniforms()
{
    //Update framebuffer size and projection matrix
    glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

    ProjectionMatrix = glm::mat4(1.f);
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
}

//Constructors & Distructors
GameEngine::GameEngine(const char* title, const int Window_Width, const int Window_Height, const int GL_Version_Major, const int GL_Version_Minor, bool resizable
)
    : Window_Width(Window_Width),window_Height(Window_Height), GL_Version_Major(GL_Version_Major),GL_Version_Minor(GL_Version_Minor)
{
    //Init variables
    this->frameBufferHeight = this->window_Height;
    this->frameBufferWidth = this->Window_Width;
    this->window = nullptr;

    this->camPosition = glm::vec3(0.f, 0.f, 1.f);
    this->worldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3 (0.f, 0.f, -1.f);

    this->fov = 90.f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.f;

    //Run all the initialisation functions
    this->initGLFW();
	this->initWindow(title,resizable);
    this->initGLEW();
    this->initOpenGLOptions();

    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initObjFromFile();
    this->initMeshes();
    this->initLights();
    this->initUniforms();
}

GameEngine::~GameEngine()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    //Delete the elements vectors
    for (size_t i = 0; i < this->shaders.size(); i++)
    {
        delete this->shaders[i];
    }

    for (size_t i = 0; i < this->textures.size(); i++)
    {
        delete this->textures[i];
    }

    for (size_t i = 0; i < this->materials.size(); i++)
    {
        delete this->materials[i];
    }

    for (size_t i = 0; i < this->meshes.size(); i++)
    {
        delete this->meshes[i];
    }

    for (size_t i = 0; i < this->lights.size(); i++)
    {
        delete this->lights[i];
    }
}


//Accessor
int GameEngine::GetWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

//Modifiers
void GameEngine::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//Functions
void GameEngine::update()
{
    //Update input
    glfwPollEvents();

    
}

void GameEngine::render()
{
    //Update--
    //updateInput(window);

    //Draw--
    //Clear
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Update the uniforms
    this->updateUniforms();

    //Update uniforms
    this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    //Use program
    this->shaders[SHADER_CORE_PROGRAM]->use();

    //Activate texture
    this->textures[TEX_GEORGE]->bind(0);
    this->textures[TEX_GEORGE_SPECULAR]->bind(1);

    //Draw
    this->meshes[0]->render(this->shaders[SHADER_CORE_PROGRAM]);

    this->textures[TEX_PANZER]->bind(0);
    this->textures[TEX_PANZER_SPECULAR]->bind(1);

    this->meshes[1]->render(this->shaders[SHADER_CORE_PROGRAM]);

    //End draw
    glfwSwapBuffers(window);
    glFlush();

    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::frameBuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH);
}