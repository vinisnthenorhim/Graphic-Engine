#ifndef PROJECTION_H
#define PROJECTION_H

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <openGL/raii/opengl.raii.h>

class Projection
{
public:
  Projection(SDL_Window* window)
  {
    this->window = window;
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    projection = glm::ortho(
        -(float)width/2,
        (float)width/2,
        -(float)height/2,
        (float)height/2
    );   
  }
  void updateProjection(GLuint& program)
  {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    projection = glm::ortho(
        -(float)width/2,
        (float)width/2,
        -(float)height/2,
        (float)height/2
    );               
    if(projectionLocation == -1) projectionLocation = glGetUniformLocation(program, "projection");

    glUniformMatrix4fv(
        projectionLocation,   
        1,                     
        GL_FALSE,             
        glm::value_ptr(projection) 
    );
    std::cout << "[OPENGL] Window is Sizing!" << '\n';
  }
  private:
    SDL_Window* window;
    GLint projectionLocation = -1;
    glm::mat4 projection;
};

#endif