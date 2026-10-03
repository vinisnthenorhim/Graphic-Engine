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
std::vector<glm::vec3> inst =
{
    {0.0f, 0.0f, 0.0f},   // instance 0: at origin
    {200.0f, 0.0f, 0.0f},   // instance 1: 2 units to the right
    {-200.0f, 0.0f, 0.0f}   // instance 2: 2 units to the left
};



void ObjectRender::resourceLoad(const RenderStoreResource resource)
{
  this->type = resource.type;
  this->visible = resource.visible;
  std::cout << "[OPENGL]"  << " Resource Load " << '\n';  

    vao.bind();                              // ← ADD THIS FIRST, explicitly

    vbo.bind();
    vbo.data(DefaultMeshObject::vertex);
    vao.linkAttrib(0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.linkAttrib(1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    instanceBuffer.bind();
    instanceBuffer.data(inst);
    vao.linkAttrib(2, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
    glVertexAttribDivisor(2, 1);

    ebo.bind();
    ebo.data(DefaultMeshObject::indices);    // ← now binds EBO *while VAO is active* — gets recorded correctly

    vao.unbind();
  std::cout << "[OPENGL]"  << " Buffer created " << '\n'; 




}


void ObjectRender::render()
{
  
    vao.bind();                 
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 3);
    vao.unbind();

}