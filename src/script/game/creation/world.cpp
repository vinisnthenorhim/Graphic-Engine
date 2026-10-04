#include <iostream>
#include <iomanip>

#include "_world.h"

World::World()
{
  lastFrame = SDL_GetTicksNS();
  std::cout << std::fixed << std::setprecision(6);
}

const RenderStoreResource World::rendererResourceStore() const 
{ 
  return 
  { 
    &type, 
    &visible,
    &speedX, 
    &speedY,
    &positionX,
    &positionY,
    &positionZ,
    &scaleX,
    &scaleY,
    &scaleZ,    
    &rotationX,
    &rotationY,
    &rotationZ,
  }; 
}; 

RenderObjectPosition World::savePosition()
{
  return 
  { 
    &positionX,
    &positionY,
    &positionZ,
    &scaleX,
    &scaleY,
    &scaleZ,    
    &rotationX,
    &rotationY,
    &rotationZ,
  }; 
}

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



void World::velocityUpdate( )
{
  int playerId = -1; 
  const int size = exist.size();
  for (int a = 0; a < size; a++)
  {
    if (type[a] == Type::Player)
    {
      playerId = a;
      break;
    }
  }

  if (playerId == -1) return; 

  const bool* keyboardState = SDL_GetKeyboardState(NULL);

  struct KeyBinding { SDL_Scancode key; std::vector<float>& axis; float sign; float& heldTime; };

  static float holdA = 0.0f, holdD = 0.0f, holdW = 0.0f, holdS = 0.0f;

  KeyBinding bindings[] = {
    { SDL_SCANCODE_A, velocityX, -1.0f, holdA },
    { SDL_SCANCODE_D, velocityX, +1.0f, holdD },
    { SDL_SCANCODE_W, velocityY, +1.0f, holdW },
    { SDL_SCANCODE_S, velocityY, -1.0f, holdS },
  };

  for (auto& b : bindings)
  {
    if (keyboardState[b.key])
    {
      dirty[playerId] = true;
      b.heldTime += secondFrame;
      b.axis[playerId] = b.sign * b.heldTime;
      std::cout << velocityX[playerId] << '\t' << velocityY[playerId] << '\n';
    }
    else
    {
      b.heldTime = 0.0f; 
    }
  }
}