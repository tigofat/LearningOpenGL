#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include "glm/glm.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include <glm/gtc/type_ptr.hpps>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shaders.h"
#include "error_handling.h"
#include "Renderer.h"
#include "Texture.h"


#define WORKING_DIR "C:/Users/tigra_/Desktop/cc/learning_opengl/LearningOpenGL"
#define PROJECT_DIR "C:/Users/tigra_/Desktop/cc/learning_opengl"


int main(void)
{

    const static int width = 800;
    const static int height = 600;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, width, height);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // Regularing frame rate
    glfwSwapInterval(1);

    // WARNING: call glewInit() after glfwMakeContextCurrent(window)
    glewInit();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,  0.5f, 1.0f
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        // 1, 2, 3    // second triangle
    };

    VertexArray vao;

    VertexBuffer vbo(vertices, 3 * 5 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(VertexBufferLayoutElement { GL_FLOAT, 3, GL_FALSE} );
    layout.Push(VertexBufferLayoutElement { GL_FLOAT, 2, GL_FALSE} );
    vao.AddBuffer(vbo, layout);

    IndexBuffer ibo(indices, 3);

    Texture texture1(WORKING_DIR"/res/textures/wall.jpg");
    Texture texture2(WORKING_DIR"/res/textures/container.jpg");

    // unsigned int vao;
    // GLCall(glGenVertexArrays(1, &vao));
    // GLCall(glBindVertexArray(vao));

    // unsigned int vbo;
    // GLCall(glGenBuffers(1, &vbo));
    // GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    // GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), vertices, GL_STATIC_DRAW));

    // GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * 2 * sizeof(float), (void*)0));
    // GLCall(glEnableVertexAttribArray(0));

    // GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * 2 * sizeof(float), (void*) (3 * sizeof(float))));
    // GLCall(glEnableVertexAttribArray(1));

    // unsigned int ibo;
    // GLCall(glGenBuffers(1, &ibo));
    // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    // GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    // GLCall(glBindVertexArray(0));
    // GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();

    ShaderProgramSource shaderSource = ParseShader(WORKING_DIR"/res/shaders/Basic.shader");

    ShaderProgram shaderProgram;
    Shader vertexShader = Shader {GL_VERTEX_SHADER, shaderSource.VertexShader.c_str()};
    Shader fragmentShader = Shader {GL_FRAGMENT_SHADER, shaderSource.FragmentShader.c_str()};
    shaderProgram.AttachShader(vertexShader);
    shaderProgram.AttachShader(fragmentShader);
    shaderProgram.Link();

    shaderProgram.Bind();
    shaderProgram.SetUniform1i("u_Texture1", 0);
    texture1.Bind(0);
    shaderProgram.SetUniform1i("u_Texture2", 1);
    texture2.Bind(1);

    shaderProgram.Unbind();

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // shaderProgram.Bind();

        // glBindVertexArray(vao);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        renderer.Draw(vao, ibo, shaderProgram);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}