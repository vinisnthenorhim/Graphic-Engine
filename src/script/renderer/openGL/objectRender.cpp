#include "objectRender.h"
struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
};
struct DefaultMeshObject
{
    static inline std::vector<Vertex> vertex =
    {
        {{-20.0f, -20.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 20.0f, -20.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 20.0f,  20.0f, 0.0f}, {1.0f, 1.0f}},
        {{-20.0f,  20.0f, 0.0f}, {0.0f, 1.0f}}
    };
    static inline std::vector<uint32_t> indices =
    { 0, 1, 2, 0, 2, 3};
};

void ObjectRender::resourceLoad(const RenderStoreResource resource)
{
  this->type = resource.type;
  this->visible = resource.visible;
  std::cout << "[OPENGL]"  << " Resource Load " << '\n';  

  vbo.data(DefaultMeshObject::vertex);
  ebo.data(DefaultMeshObject::indices);
  vao.linkAttrib(0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
  vao.linkAttrib(1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, uv));

  std::cout << "[OPENGL]"  << " Buffer created " << '\n';  
}


void ObjectRender::render()
{
  

}