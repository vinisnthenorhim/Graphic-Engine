// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <cmath>

#include "_GLcore.h"

GLRenderer::GLRenderer(SDL_Window* window)
:context(window),program("shaders/triangle.vert", "shaders/triangle.frag"), projection(window)
{
  program.bind();
  projection.updateProjection(program.program());  
  pastTime = SDL_GetTicks()/1000;
}

GLRenderer::~GLRenderer()
{}

void GLRenderer::screenUpdate()
{
  update = true;

}
void GLRenderer::resourceDataLoad(const RenderStoreResource& resource, RenderObjectPosition objectPosition, RenderVelocity objectVelocity)
{
  compute.resourceLoad(objectVelocity);
  objectRender.resourceLoad(resource);
}

void GLRenderer::render()
{
  Uint64 currentTime = SDL_GetTicks()/ 1000;
  if(update && (currentTime - pastTime) >= delay)
  {
    program.bind();
    projection.updateProjection(program.program());
    update = false;
    pastTime = currentTime;
  }
  compute.calculate();
  program.bind();
  objectRender.render();
}
