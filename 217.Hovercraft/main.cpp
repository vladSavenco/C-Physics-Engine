#include "libs.h"

Vertex vertices[] =
{
    //Position                      //Color                         //Texcoords
    glm::vec3(0.0f,0.5f,0.f),       glm::vec3(1.f,0.f,0.f),         glm::vec2(0.f,1.f),
    glm::vec3(-0.5f,-0.5f,0.f),     glm::vec3(0.f,1.f,0.f),         glm::vec2(0.f,0.f),
    glm::vec3(0.5f,-0.5f,0.f),      glm::vec3(0.f,0.f,1.f),         glm::vec2(1.f,0.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
    0,1,2
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

bool loadShaders(GLuint& program)
{
    bool loadSuccess = true;
    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";

    std::ifstream in_file;

    //Vertex
    in_file.open("vertex_core.glsl");

    if (in_file.is_open())
    {
        while (std::getline(in_file, temp))
            src += temp + "\n";
    }
    else
    {
        std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = src.c_str();
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
        std::cout << infoLog << "\n";
        loadSuccess = false;
    }

    temp = "";
    src = "";

    //Fragment
    in_file.open("fragment_core.glsl");

    if (in_file.is_open())
    {
        while (std::getline(in_file, temp))
            src += temp + "\n";
    }
    else
    {
        std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << "\n";
    loadSuccess = false;
    }

    in_file.close();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSrc = src.c_str();
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << "\n";
        std::cout << infoLog << "\n";
        loadSuccess = false;
    }

    //Program
    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::LOADSHADERS::COULD_NOT_CLINK_PROGRAM" << "\n";
        std::cout << infoLog << "\n";
        loadSuccess = false;
    }

    //End
    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccess;
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

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Vlad n Friends Incorporated ",NULL,NULL);

    glfwSetFramebufferSizeCallback(window, frameBuffer_resize_callback);

    //glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
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
    GLuint core_program;
    if (!loadShaders(core_program))
        glfwTerminate();

    //Model

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

    //Bind VAO 0
    glBindVertexArray(0);

    //Testing GLEW
    /*if (GLEW_OK != err)
    {
        std::cout<<(stderr, "Error: %s\n", glewGetErrorString(err));
    }
        std::cout<<(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    */

    //Main loop
    while(!glfwWindowShouldClose(window))
    {
        //Update input--
        glfwPollEvents();

        //Update--
        updateInput(window);

        //Draw--
        //Clear
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //Use a program
        glUseProgram(core_program);

        //Bind vertex array object
        glBindVertexArray(VAO);

        //Draw
        glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

        //End draw
        glfwSwapBuffers(window);
        glFlush();
    }

    //End of Program
    glfwDestroyWindow(window);
    glfwTerminate();

    //Delete program
    glDeleteProgram(core_program);

    return 0;
}