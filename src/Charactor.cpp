#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include "Charactor.hpp"

Charactor::Charactor() {}

Charactor::~Charactor() {}

void Charactor::update() {
  
}

void Charactor::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
