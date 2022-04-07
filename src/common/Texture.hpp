#pragma once

#include "../common/Vec.hpp"
#include <GLFW/glfw3.h>
#include <string>

class Texture {
  private:
    GLuint texName;
    Size size;

  public:
    Texture(std::string path, GLint filter = GL_LINEAR);
    ~Texture();

    void Draw(const Size vpSize, const Point dst);
    void Draw(const Size vpSize, const Point dst, const Point src, const Size srcRect);
};
