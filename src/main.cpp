#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Globals.h"
#include "ShaderProgram.h"

int main(int argc, char* args[])
{
    GLFWwindow* window;

    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(640,480, "Hello World", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
	glewInit();

    Globals::initGlobals();

    //setup test shader
	ShaderProgram* shader = new ShaderProgram();
    
    char* vertexShader = R"glsl(
    #version 150 core

    in vec3 position;
    out vec3 pos;

    void main()
    {
        pos = position;
        gl_Position = vec4(position, 1.0);
    }
    )glsl";

    char* fragmentShader = R"glsl(
    #version 150 core

    in vec3 pos;
    out vec4 outColor;

    void main()
    {
        outColor = vec4(pos.xy, 0.5 - sqrt(pos.x * pos.x + pos.y * pos.y)/10,1);
    }
    )glsl";

    shader->addShader(GL_VERTEX_SHADER, vertexShader);
    shader->addShader(GL_FRAGMENT_SHADER, fragmentShader);
    shader->link();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,   0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
    }; 
    
    GLuint vao, vbo = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader->vertexAttribPointer("position", 3, GL_FLOAT, GL_FALSE, 0, 0);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}