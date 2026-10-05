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
  this->type      = resource.type     ;
  this->visible   = resource.visible  ;
  this->positionX = resource.positionX;
  this->positionY = resource.positionY;
  this->positionZ = resource.positionZ;
  this->scaleX    = resource.scaleX   ;
  this->scaleY    = resource.scaleY   ;
  this->scaleZ    = resource.scaleZ   ;
  this->rotationX = resource.rotationX;
  this->rotationY = resource.rotationY;
  this->rotationZ = resource.rotationZ;

  std::cout << "[OPENGL]"  << " Resource Load " << '\n';  

    vao.bind();                             

    vbo.data(DefaultMeshObject::vertex);
    vao.linkAttrib(0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    vao.linkAttrib(1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    instanceBuffer.data(inst);
    vao.linkAttrib(2, 3, GL_FLOAT, sizeof(glm::vec3), (void*)0);
    glVertexAttribDivisor(2, 1);

    ebo.bind();
    ebo.data(DefaultMeshObject::indices);   

    vao.unbind();

  std::cout << "[OPENGL]"  << " Buffer created " << '\n'; 
}


void ObjectRender::render()
{
  glClearColor( 0.0f, 0.1f, 0.2f, 0.2f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  int objectQuantity = visible->size();
  vao.bind();                 
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, objectQuantity);
  vao.unbind();

}