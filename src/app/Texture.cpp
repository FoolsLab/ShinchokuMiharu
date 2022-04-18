#include "Texture.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stb_image.h>
#include <array>

static const std::array<GLfloat, 8> vertex = {-1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0};
static const std::array<GLfloat, 8> texCoord = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
static const std::array<GLubyte, 8> indices = {0, 1, 2, 3};

Texture::Texture(std::string path, GLint filter) {
    int width, height, bpp;

    auto pixels = stbi_load(path.c_str(), &width, &height, &bpp, 4);
    this->size = Size(width, height);

    glGenTextures(1, &this->texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, pixels);

    stbi_image_free(pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

Texture::~Texture() { glDeleteTextures(1, &this->texName); }

void Texture::Draw(const Size vpSize, const Point dst) const {
    this->Draw(vpSize, dst, {0, 0}, size);
}
void Texture::Draw(const Size vpSize, const Point dst, const Point src,
                   const Size srcRect) const {
    this->Draw(vpSize, dst, {0, 0}, size, 1.0f);
}
void Texture::Draw(const Size vpSize, const Point dst, const Point src,
                   const Size srcRect, float scale) const {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texName);

    glLoadIdentity();

    glTranslatef(-1.0f, 1.0f, 0.0f);
    glScalef(scale * srcRect.x / vpSize.x, scale * srcRect.y / vpSize.y, 1.0f);
    glTranslatef(1.0f + dst.x * 2 / srcRect.x / scale, -1.0f - dst.y * 2 / srcRect.y / scale,
                 0.0f);

    auto tmpTexCoord = texCoord;
    for(size_t i = 0; i < 4; i++){
        tmpTexCoord[i * 2] = (src.x + tmpTexCoord[i * 2] * srcRect.x) / size.x;
        tmpTexCoord[i * 2 + 1] = (src.y + tmpTexCoord[i * 2 + 1] * srcRect.y) / size.y;
    }

    glVertexPointer(2, GL_FLOAT, 0, vertex.data());
    glTexCoordPointer(2, GL_FLOAT, 0, tmpTexCoord.data());

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices.data());

    glDisable(GL_TEXTURE);
    glDisable(GL_BLEND);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
