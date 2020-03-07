#include "libs.h"

Vertex vertices[] =
{
    //Position                      //Color                         //Texcoords                 //Normals
    glm::vec3(-0.5f,0.5f,0.f),      glm::vec3(1.f,0.f,0.f),         glm::vec2(0.f,1.f),         glm::vec3(0.f,0.f,-1.f),

    glm::vec3(-0.5f,-0.5f,0.f),     glm::vec3(0.f,1.f,0.f),         glm::vec2(0.f,0.f),         glm::vec3(0.f,0.f,-1.f),

    glm::vec3(0.5f,-0.5f,0.f),      glm::vec3(0.f,0.f,1.f),         glm::vec2(1.f,0.f),         glm::vec3(0.f,0.f,-1.f),

    glm::vec3(0.5f,0.5f,0.f),       glm::vec3(1.f,1.f,0.f),         glm::vec2(1.f,1.f),         glm::vec3(0.f,0.f,-1.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
    0,1,2, //triangle 1
    0,2,3 //triangle 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void updateInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void frameBuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH);
}

void updateInput(GLFWwindow*window,glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
{
    //Movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position.z -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position.z += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position.x -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position.x += 0.01f;
    }

    //Rotation
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        rotation.y -= 1.f;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        rotation.y += 1.f;
    }

    //Scale
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        scale += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        scale -= 0.1f;
    }
}

int main()
{
    const int windowWidth = 800, windowHeight = 600;
    int frameBufferWidth = 0, frameBufferHeight = 0;

    //GLFW initialisation 
    glfwInit();

    //Test GLFW
    /*if (!glfwInit()) {
        std::cout<<("failed to init glfw");
    }*/

    //Creating the window 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Vlad n Friends Incorporated ", NULL, NULL);

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glfwSetFramebufferSizeCallback(window, frameBuffer_resize_callback);

    //glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    //Check if window was created
    /*if (nullptr == window)
    {
        std::cout<<("failed to create window");
        glfwTerminate();

        return EXIT_FAILURE;
    }*/

    glfwMakeContextCurrent(window);//Important

    //Initialising GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    //Opengl options
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Shader init
    Shader core_program("vertex_core.glsl", "fragment_core.glsl");

    //Model mesh

    //VAO, VBO, EBO
    //GEN VAO And BIND
    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //GEN VAO And BIND and SEND DATA
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //GEN EBO and BIND and SEND DATA
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

    //Testing GLEW
    /*if (GLEW_OK != err)
    {
        std::cout<<(stderr, "Error: %s\n", glewGetErrorString(err));
    }
        std::cout<<(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    */

    //Texture 0
    Texture texture0("Images/panzer.jpg", GL_TEXTURE_2D,0);

    //Texture 1
    Texture texture1("Images/george.jpg", GL_TEXTURE_2D,1);

    //Material 0
    Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture0.getTextureUnit(), texture1.getTextureUnit());

    //Init Matrieces
    glm::vec3 position(0.f);
    glm::vec3 rotation(0.f);
    glm::vec3 scale(1.f);

    glm::mat4 ModelMatrix(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);

    glm::vec3 camPosition(0.f, 0.f, 1.f);
    glm::vec3 worldUp(0.f, 1.f, 0.f);
    glm::vec3 camFront(0.f, 0.f, -1.f);
    glm::mat4 ViewMatrix(1.f);
    ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;
    glm::mat4 ProjectionMatrix(1.f);
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);

    //Lights
    glm::vec3 lightPos0(0.f, 0.f, 1.f);

    //Init uniforms
    core_program.setMat4fv(ModelMatrix, "ModelMatrix");
    core_program.setMat4fv(ViewMatrix, "ViewMatrix");
    core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    core_program.setVec3f(lightPos0, "lightPos0");
    core_program.setVec3f(camPosition, "cameraPos");

    //Main loop
    while(!glfwWindowShouldClose(window))
    {
        //Update input--
        glfwPollEvents();
        updateInput(window, position, rotation, scale);

        //Update--
        updateInput(window);

        //Draw--
        //Clear
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //Update uniforms
        core_program.set1i(texture0.getTextureUnit(), "texture0");
        core_program.set1i(texture1.getTextureUnit(), "texture1");

        material0.sendToShader(core_program);

        //Move, rotate and sacale
        ModelMatrix = glm::mat4(1.f);
        ModelMatrix = glm::translate(ModelMatrix, position);
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
        ModelMatrix = glm::scale(ModelMatrix, scale);


        core_program.setMat4fv(ModelMatrix, "ModelMatrix");

        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

        ProjectionMatrix = glm::mat4(1.f);
        ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferHeight, nearPlane, farPlane);

        core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

        //Use a program
        core_program.use();

        //Activate texture
        texture0.bind();
        texture1.bind();

        //Bind vertex array object
        glBindVertexArray(VAO);

        //Draw
        //glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
        glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

        //End draw
        glfwSwapBuffers(window);
        glFlush();

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //End of Program
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}