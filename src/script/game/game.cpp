#include "_game.h"

Game::Game(Renderer& renderer)
{
  renderer.resourceDataLoad(world.rendererResourceStore());
  world.createObject(Type::Player);
}

void Game::render(Renderer& renderer)
{

  world.secondPerFrame();
  const int& size = world.dirtyObject().size();
  for(int a = 0; a < size; a++)
  {
    if (world.dirtyObject()[a])
    {
      renderer.render();
    }
  }
  const bool* keyboardState = SDL_GetKeyboardState(NULL);
  if (keyboardState[SDL_SCANCODE_A])
  {
    std::cout << "Hold Time is: " << world.velocityUpdate(0) << 's' << '\n';
  }

}

void Game::event(const SDL_Event* event)
{

  if (event->key.key == SDLK_Q && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
  {
    world.createObject(Type::Player);
  }
  
}