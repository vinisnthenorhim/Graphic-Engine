#pragma once

#include <vector>
#include <optional>
#include <renderObject/enum/enum.h>
#include <renderObject/enum/struct.h>
#include <openGL/raii/opengl.raii.h>


class ObjectRender
{   
  public:
    void resourceLoad(const RenderStoreResource resource);
    void render();

  private:
    VAO vao;
    VBO vbo;
    VBO instanceBuffer;
    EBO ebo;

    const std::vector<Type>* type;
    const std::vector<bool>* visible;
  
};