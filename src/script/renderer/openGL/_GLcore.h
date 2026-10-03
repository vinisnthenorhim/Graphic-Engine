#ifndef OPEN_GL_H
#define OPEN_GL_H
#include <iostream>
#include <SDL3/SDL.h>

#include "projection.h"
#include "context.h"
#include "objectRender.h"
#include <random>

class GLRenderer
{
  public:
    GLRenderer(SDL_Window* window);
    ~GLRenderer();
    void resourceDataLoad(const RenderStoreResource resource);
    void screenUpdate();
    void render();
  private:

    GlContext context;
    ShaderProgram program;
    Projection projection;
    ObjectRender objectRender;

    bool update = false;
    Uint64 pastTime;
    const float delay = 0.3;

    VBO vboPlayer;
    VAO vaoPlayer;
    EBO eboPlayer;


    // std::vector<glm::vec3> vertices;

    // std::random_device rd;
    // std::mt19937 gen(rd());

    // std::uniform_real_distribution<float> dist(-500.0f, 500.0f);

    };


#endif