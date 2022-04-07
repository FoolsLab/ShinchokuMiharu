#include "Texture.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stb_image.h>

static const GLfloat vertex[] = {-1.0, 1.0, -1.0, -1.0, 1.0, -1.0, 1.0, 1.0};
static const GLfloat texCoord[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
static const GLubyte indices[] = {0, 1, 2, 3};

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

void Texture::Draw(const Size vpSize, const Point dst) { this->Draw(vpSize, dst, {0, 0}, size); }
void Texture::Draw(const Size vpSize, const Point dst, const Point src, const Size srcRect) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texName);

    glLoadIdentity();

    glTranslatef(-1.0f, 1.0f, 0.0f);
    glScalef(size.x / vpSize.x, size.y / vpSize.y, 1.0f);
    glTranslatef(1.0f + dst.x * 2 / size.x, -1.0f - dst.y * 2 / size.y, 0.0f);
    glVertexPointer(2, GL_FLOAT, 0, vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoord);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);

    glDisable(GL_TEXTURE);
    glDisable(GL_BLEND);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
