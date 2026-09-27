#include "_game.h"

Game::Game(Renderer& renderer)
{
  renderer.resourceDataLoad(world.rendererResourceStore());
  world.createObject(Type::Player);
}

void Game::render(Renderer& renderer)
{
  // world.updateData();
  world.secondPerFrame();
  world.velocityUpdate( 0, 0, 0);

}

void Game::event(const SDL_Event* event)
{
  if (event->key.key == SDLK_Q && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
  {
      world.createObject(Type::Player);
  }
  
}