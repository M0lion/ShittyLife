#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class MeshData
{
public:
    std::vector<glm::vec3>* positions;
    std::vector<glm::vec3>* normals;
    std::vector<glm::vec4>* colors;
    std::vector<glm::vec2>* uvs;

    MeshData();
    ~MeshData();

    void bind();
};