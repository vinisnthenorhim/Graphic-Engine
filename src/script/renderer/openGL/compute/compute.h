#pragma once

#include <openGL/raii/opengl.raii.h>
#include <renderObject/enum/struct.h>

class Compute
{
  public:
    Compute()
    :computeProg("")
    {}
    void resourceLoad(RenderVelocity& renderVelocity);
    void calculate();

  private:
    ComputeProgram computeProg;
    SSBO ssbo;
};