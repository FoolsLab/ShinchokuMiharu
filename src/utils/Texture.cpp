#include "Texture.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stb_image.h>

Texture::Texture(std::string path, GLint filter) {
    int width;
    int height;
    int bpp;

    auto pixels = stbi_load(path.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &this->texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, pixels);

    stbi_image_free(pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

Texture::~Texture() { glDeleteTextures(1, &this->texName); }
