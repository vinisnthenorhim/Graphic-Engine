#include "_game.h"

Game::Game(Renderer& renderer)
{
    renderer.resourceDataLoad(world.rendererResourceStore());
}

void Game::render(Renderer& renderer)
{
}

void Game::event(const SDL_Event* event)
{
    if (event->key.key == SDLK_Q && event->type == SDL_EVENT_KEY_DOWN && !event->key.repeat)
    {
        world.createObject(Type::Player);
    }
}