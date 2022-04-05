#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Texture {
  private:
    GLuint texName;
  public:
    Texture(std::string path, GLint filter = GL_LINEAR);
    ~Texture();
};
