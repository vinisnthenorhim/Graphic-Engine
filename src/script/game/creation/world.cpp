#include <iostream>
#include <iomanip>

#include "_world.h"

World::World()
{
  lastFrame = SDL_GetTicks();
  std::cout << std::fixed << std::setprecision(4);
}

const RenderStoreResource World::rendererResourceStore() const { return {&type, &visible}; }; 

uint32_t World::createObject(Type objectType)
{
  id++;

  type.push_back(objectType);

  positionX.push_back(0.0f);
  positionY.push_back(0.0f);
  positionZ.push_back(0.0f);

  scaleX.push_back(1.0f);
  scaleY.push_back(1.0f);
  scaleZ.push_back(1.0f);

  rotationX.push_back(0.0f);
  rotationY.push_back(0.0f);
  rotationZ.push_back(0.0f);

  velocityX.push_back(3.0f);
  velocityY.push_back(3.0f);
  velocityZ.push_back(0.0f);

  visible.push_back(true);
  exist.push_back(true);

  std::cout << "Object No: " << id << '\n';

  return id;
}
void World::secondPerFrame()
{
  float currentFrame = SDL_GetTicks();

  secondFrame = ( currentFrame - lastFrame)/1000;
  lastFrame = currentFrame;
}

void World::velocityUpdate( uint32_t id, float speedX, float speedY )
{
  const bool* keyboardState = SDL_GetKeyboardState(NULL);
  if(keyboardState[SDL_SCANCODE_B])
  {
    holdtime += secondFrame;
    std::cout << "Hold Time is: " << holdtime << 's' << '\n';
  }
  else
  {
    holdtime = 0;
  }
}