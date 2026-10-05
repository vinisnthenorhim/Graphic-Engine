#include <iostream>

#include "compute.h"

Compute::Compute()
:velocityComputeProg("shaders/velocity.comp")
{
  entityUniformLoc = glGetUniformLocation  (velocityComputeProg.program(), "entityCount");
  deltaTimeUniforLoc = glGetUniformLocation(velocityComputeProg.program(), "deltaTime");



}

void Compute::resourceLoad(RenderVelocity& renderVelocity)
{

  this->deltaTime = renderVelocity.secondFrame;
  this->velocityX = renderVelocity.velocityX;
  this->velocityY = renderVelocity.velocityY;
  this->velocityZ = renderVelocity.velocityZ;

  // entityCount = velocityX->size();

  // modelMatrices.data(static_cast<GLsizeiptr>(entityCount * sizeof(glm::mat4)), 4);
  // positionVec4.data(static_cast<GLsizeiptr>(entityCount * sizeof(glm::vec4)), 0);
  // positionVec4.clear();
  ssboVelocityX.data(*velocityX, 1);
  ssboVelocityY.data(*velocityY, 2);
  ssboVelocityZ.data(*velocityZ, 3);
}



void Compute::calculate()
{

entityCount = velocityX->size();
if (entityCount == 0) return;

if (entityCount > capacity)
{
  capacity = entityCount;
  positionVec4.data(capacity * sizeof(glm::vec4), 0);
  positionVec4.clear();
  modelMatrices.data(capacity * sizeof(glm::mat4), 4);
}
  ssboVelocityX.updateData(*velocityX);
  ssboVelocityY.updateData(*velocityY);
  ssboVelocityZ.updateData(*velocityZ);

  // std::vector<float> check(velocityX->size());
  // glGetNamedBufferSubData(ssboVelocityX.id(), 0, check.size() * sizeof(float), check.data());
  // std::cout << check[0] << '\n';
  // std::cout << (*velocityX)[0] << '\t' << (*velocityY)[0] << '\n';

  velocityComputeProg.bind();
  // std::cout << deltaTimeUniforLoc << '\t' << entityUniformLoc << '\n';

  glUniform1f(deltaTimeUniforLoc, *deltaTime);
  glUniform1ui(entityUniformLoc, entityCount);

  glDispatchCompute((entityCount + 63) / 64, 1, 1);

  SSBO::barrier();
  glm::mat4 m(0.0f);
glGetNamedBufferSubData(modelMatrices.id(), 0, sizeof(glm::mat4), &m);
std::cout << m[3][0] << ' ' << m[3][1] << ' ' << m[3][2] << ' ' << m[3][3]
          << "  err " << glGetError() << '\n';
}