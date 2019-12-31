#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shaders.h"
#include "error_handling.h"

#define WORKING_DIR "C:/Users/tigra_/Desktop/cc/learning_opengl/LearningOpenGL"


int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // Regularing frame rate
    glfwSwapInterval(1);

    // WARNING: call glewInit() after glfwMakeContextCurrent(window)
    glewInit();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5, 0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;

    VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push(VertexBufferLayoutElement { GL_FLOAT, 2, GL_FALSE });

    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    ShaderProgramSource shaderSource = ParseShader(WORKING_DIR"/res/shaders/Basic.shader");

    ShaderProgram program;
    program.AttachShader(Shader {GL_VERTEX_SHADER, shaderSource.VertexShader.c_str()});
    program.AttachShader(Shader {GL_FRAGMENT_SHADER, shaderSource.FragmentShader.c_str()});
    program.Link();

    int location = glGetUniformLocation(program.GetRendererId(), "u_Color");
    Assert(location != -1);

    float r = 0.0f;
    float increment = 0.05f;

    program.Unbind();
    vb.Unbind();
    ib.Unbind();
    va.Unbind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        program.Bind();
        GLCall(glUniform4f(location, r, 0.3, 0.8, 1.0));

        va.Bind();
        ib.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}