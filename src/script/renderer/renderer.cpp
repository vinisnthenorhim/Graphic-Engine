#include "_renderer.h"

Renderer::Renderer(SDL_Window* window)
: GlRenderer(window)
{

}


Renderer::~Renderer()
{

}
void Renderer::screenUpdate(const SDL_Event* event)
{
  if (event->type == SDL_EVENT_WINDOW_RESIZED)
  {
    GlRenderer.screenUpdate();
  }
}
void Renderer::resourceDataLoad(const RenderStoreResource& resource, RenderObjectPosition objectPosition, RenderVelocity objectVelocity)
{
  GlRenderer.resourceDataLoad(resource, objectPosition, objectVelocity);
}

bool Renderer::render()
{
  GlRenderer.render();
  return true;
}
