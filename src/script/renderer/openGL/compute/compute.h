#pragma once

#include <glm/glm.hpp>
#include <openGL/raii/opengl.raii.h>
#include <renderObject/enum/struct.h>

class Compute
{
  public:
    Compute();

    void resourceLoad(RenderVelocity& renderVelocity);
    void calculate();

  private:
    ComputeProgram velocityComputeProg;
    SSBO ssboVelocityX;
    SSBO ssboVelocityY;
    SSBO ssboVelocityZ;
    SSBO positionVec4;
    SSBO modelMatrices;

    int entityCount = 0;
    size_t capacity = 0;
    GLint entityUniformLoc = -1;
    GLint deltaTimeUniforLoc = -1;

    float* deltaTime;

    std::vector<float>* velocityX    ;
    std::vector<float>* velocityY    ;
    std::vector<float>* velocityZ    ;


};