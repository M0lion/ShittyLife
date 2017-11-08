#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "ShaderProgram.h"

class ColoredVertex
{
public:
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec4 color;

    static inline void setVertexAttribs(ShaderProgram* shader)
    {
        int stride = sizeof(glm::vec3) * 2;
        stride += sizeof(glm::vec4);
        shader->vertexAttribPointer("position", 3, GL_FLOAT, false, stride, 0);
        shader->vertexAttribPointer("normal", 3, GL_FLOAT, false, stride, (void*)sizeof(glm::vec3));
        shader->vertexAttribPointer("color", 4, GL_FLOAT, false, stride, (void*)(sizeof(glm::vec3) * 2));
    }
};