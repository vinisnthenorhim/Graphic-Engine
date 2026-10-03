#include <iostream>
#include <iomanip>

#include "_world.h"

World::World()
{
  lastFrame = SDL_GetTicksNS();
  std::cout << std::fixed << std::setprecision(6);
}

const RenderStoreResource World::rendererResourceStore() const { return {&type, &visible}; }; 

uint32_t World::createObject(Type objectType)
{

  type.push_back(objectType);
  dirty.push_back(false)    ;

  positionX.push_back(0.0f);
  positionY.push_back(0.0f);
  positionZ.push_back(0.0f);

  scaleX.push_back(1.0f)   ;
  scaleY.push_back(1.0f)   ;
  scaleZ.push_back(1.0f)   ;

  rotationX.push_back(0.0f);
  rotationY.push_back(0.0f);
  rotationZ.push_back(0.0f);

  velocityX.push_back(0.0f);
  velocityY.push_back(0.0f);
  velocityZ.push_back(0.0f);

  speedX.push_back(3.0f)   ;
  speedY.push_back(3.0f)   ;

  visible.push_back(true)  ;
  exist.push_back(true)    ;
  id++;

  std::cout << "Object No: " << id << '\n';

  return id;
}
void World::secondPerFrame()
{
  float currentFrame = SDL_GetTicksNS();

  secondFrame = ( currentFrame - lastFrame)/1000000000;
  lastFrame = currentFrame;
}



float World::velocityUpdate( uint32_t id )
{
  const bool* keyboardState = SDL_GetKeyboardState(NULL);
  if(keyboardState[SDL_SCANCODE_A])
  {
    dirty[id] = true;
    holdtime += secondFrame;
    std::cout << "Hold Time is: " << holdtime << 's' << '\n';
    return secondFrame;
  }
  return 0;
  // else if (event->type == SDL_EVENT_KEY_UP)
  // {
  //   holdtime = 0;
  // }
}