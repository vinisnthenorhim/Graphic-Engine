#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL.h>

#include <vector>
#include <glm/glm.hpp>

#include <renderObject/enum/enum.h>
#include <renderObject/enum/struct.h>

class World
{
  public:
    World();
    const RenderStoreResource rendererResourceStore() const; 
    const std::vector<bool>& dirtyObject() const { return dirty;};
    uint32_t createObject(Type objectType);
    float velocityUpdate( uint32_t id );
    // void 

    void secondPerFrame();

  private:
    float lastFrame;
    float secondFrame;
    
    float holdtime = 0.0f;

    uint32_t id = 0;
    std::vector<Type> type          ;
    std::vector<bool> dirty         ;

    std::vector<float> positionX    ;
    std::vector<float> positionY    ;
    std::vector<float> positionZ    ;

    std::vector<float> scaleX       ;
    std::vector<float> scaleY       ;
    std::vector<float> scaleZ       ;

    std::vector<float> rotationX    ;
    std::vector<float> rotationY    ;
    std::vector<float> rotationZ    ;

    std::vector<float> velocityX    ;
    std::vector<float> velocityY    ;
    std::vector<float> velocityZ    ;

    std::vector<float> speedX       ;
    std::vector<float> speedY       ;

    std::vector<bool> visible       ;
    std::vector<bool> exist         ;

};

#endif