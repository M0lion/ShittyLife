#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Globals.h"
#include "ShaderProgram.h"
#include "ColoredVertex.h"
#include "ColoredMesh.h"

#include "Sleep.h"

#include <stdio.h>

//called when window is resized
void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    Globals::windowWidth = width;
    Globals::windowHeight = height;
}

int main(int argc, char* args[])
{
    GLFWwindow* window;

    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(Globals::windowWidth,Globals::windowHeight, "Hello World", NULL, NULL);

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
    
    ColoredMesh mesh;

    ColoredVertex vertex;
    vertex.color = glm::vec4(1,1,1,1);
    vertex.normal = glm::vec3(1,1,1);

    vertex.pos = glm::vec3(1,0,0);
    vertex.color = glm::vec4(1,0,0,1);
    mesh.addVertex(vertex.pos, vertex.normal, vertex.color);

    vertex.pos = glm::vec3(0,0,1);
    vertex.color = glm::vec4(0,0,1,1);
    mesh.addVertex(vertex.pos, vertex.normal, vertex.color);

    vertex.pos = glm::vec3(0,1,0);
    vertex.color = glm::vec4(0,1,0,1);
    mesh.addVertex(vertex.pos, vertex.normal, vertex.color);

    mesh.load();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);  

        mesh.Draw();

        sleep((int)(1000/60.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}