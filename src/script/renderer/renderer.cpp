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
void Renderer::resourceDataLoad(const RenderStoreResource resource)
{
  GlRenderer.resourceDataLoad(resource);
}

bool Renderer::render()
{
  // return GlRenderer.render();
  return true;
}
