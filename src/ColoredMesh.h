
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "ShaderProgram.h"
#include "ColoredVertex.h"
#include "Camera.h"

class ColoredMesh
{
public:
    ColoredMesh();
    ~ColoredMesh();

    void addVertex(glm::vec3 pos, glm::vec3 normal, glm::vec4 color);
    void clearData();

    void load();

    void Draw(Camera* camera, glm::mat4 model);
private:
    GLuint vbo;
    GLuint vao;
    static ShaderProgram *shader;
    std::vector<ColoredVertex> vertices;
};