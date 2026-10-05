#ifndef RENDERER_H
#define RENDERER_H

#include <openGL/_GLcore.h>

class Renderer
{
    public:
        Renderer(SDL_Window* window);
        ~Renderer();
        void resourceDataLoad(const RenderStoreResource& resource, RenderObjectPosition objectPosition, RenderVelocity objectVelocity);

        void screenUpdate(const SDL_Event* event);
        bool render();

    private:

    GLRenderer GlRenderer;
};

#endif