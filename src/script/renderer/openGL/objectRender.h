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
    
    const std::vector<float>* speedX       ;
    const std::vector<float>* speedY       ;
      
    const std::vector<float>* positionX    ;
    const std::vector<float>* positionY    ;
    const std::vector<float>* positionZ    ;
    
    const std::vector<float>* scaleX       ;
    const std::vector<float>* scaleY       ;
    const std::vector<float>* scaleZ       ;

    const std::vector<float>* rotationX    ;
    const std::vector<float>* rotationY    ;
    const std::vector<float>* rotationZ    ;
  
};