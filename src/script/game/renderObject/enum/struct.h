#ifndef STRUCT_ENTITY_H
#define STRUCT_ENTITY_H
#include "enum.h"
#include <glm/glm.hpp>



struct RenderState
{
    bool& visible;
    bool hasBuffer = false;
};


struct MaterialHandle
{

};


struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

struct RenderStoreResource
{
    const std::vector<Type>* type;
    const std::vector<bool>* visible;
};

#endif