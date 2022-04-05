#include "Charactor.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>

Charactor::Charactor(const Window *_mainWindow)
    : mainWindow(_mainWindow), tex1("./assets/test.png") {}

Charactor::~Charactor() {}

void Charactor::update() {}

void Charactor::draw() {
    glClearColor(0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    tex1.Draw({100, 150});
}
