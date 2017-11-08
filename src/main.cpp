#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Globals.h"
#include "ShaderProgram.h"
#include "MeshData.h"

#include"Sleep.h"

#include <stdio.h>

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
    #version 130

    in vec3 position;
    out vec3 pos;

    void main()
    {
        pos = position;
        gl_Position = vec4(position, 1.0);
    }
    )glsl";

    char* fragmentShader = R"glsl(
    #version 130

    uniform float t;

    in vec3 pos;
    out vec4 outColor;

    void main()
    {
        vec3 Pos = pos;

        Pos.x += sin(t);
        Pos.y += cos(t);

        float n = sqrt((Pos.x*Pos.x)+(Pos.y*pos.y))*10;
        
        n += 10 * sin(t);

        outColor = vec4(tan(n),sin(n),cos(n),1);
    }
    )glsl";

    shader->addShader(GL_VERTEX_SHADER, vertexShader);
    shader->addShader(GL_FRAGMENT_SHADER, fragmentShader);
    shader->link();

    float vertices[] = {
        -100, -100, 0.0,
         100,  100, 0.0,
         100, -100, 0.0,
        -100, -100, 0.0,
        -100,  100, 0.0,
         100,  100, 0.0,
    }; 
    
    GLuint vao, vbo = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    shader->vertexAttribPointer("position", 3, GL_FLOAT, GL_FALSE, 0, 0);
    int t_loc = shader->getUniformLocation("t");
    
    float t = 0;

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1f(t_loc, t);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        t += 0.05f;

        sleep((int)(1000/60.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}