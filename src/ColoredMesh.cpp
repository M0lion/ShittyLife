#include "Globals.h"
#include "ColoredMesh.h"

#include "Helpers.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram *ColoredMesh::shader = nullptr;

ColoredMesh::ColoredMesh()
{
    if(shader == nullptr)
    {
        ShaderProgram *shader = new ShaderProgram();

        char* vertexShader = get_file_contents((Globals::shaderFolder + "colored.vsh").c_str());
        char* fragmentShader = get_file_contents((Globals::shaderFolder + "colored.fsh").c_str());

        shader->addShader(GL_VERTEX_SHADER, vertexShader);
        shader->addShader(GL_FRAGMENT_SHADER, fragmentShader);
        shader->link();

        delete(vertexShader);
        delete(fragmentShader);

        this->shader = shader;
    }

    glGenBuffers(1, &(this->vbo));
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glGenVertexArrays(1, &(this->vao));
    glBindVertexArray(this->vao);

    ColoredVertex::setVertexAttribs(this->shader);
}

ColoredMesh::~ColoredMesh()
{
    glDeleteBuffers(1, &(this->vbo));
    glDeleteVertexArrays(1, &(this->vao));
}

void ColoredMesh::addVertex(glm::vec3 pos, glm::vec3 normal, glm::vec4 color)
{
    ColoredVertex vertex;
    vertex.pos = pos;
    vertex.normal = normal;
    vertex.color = color;
    vertices.push_back(vertex);
}

void ColoredMesh::clearData()
{
    vertices.clear();
}

void ColoredMesh::load()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ColoredVertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);
}

void ColoredMesh::Draw()
{
    shader->use();
    glUniformMatrix4fv(shader->getUniformLocation("camera"), 1, GL_FALSE, &Globals::camera[0][0]);
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}