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
        // bool render();
    private:

        GlContext context;
        Projection projection;
        ObjectRender objectRender;

        VBO vboPlayer;
        VAO vaoPlayer;
        EBO eboPlayer;
        bool create = false;


    // std::vector<glm::vec3> vertices;

    // std::random_device rd;
    // std::mt19937 gen(rd());

    // std::uniform_real_distribution<float> dist(-500.0f, 500.0f);

    };


#endif