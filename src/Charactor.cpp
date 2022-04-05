#include "Charactor.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>

Charactor::Charactor(const Window *_mainWindow)
    : mainWindow(_mainWindow), tex1("./assets/test.png") {
    setWindowSize({512, 512});
}

Charactor::~Charactor() {}

void Charactor::setWindowPos(Point pos) { mainWindow->setWindowPos(pos); }

void Charactor::setWindowSize(Size size) {
    mainWindow->setWindowSize(size);
    glViewport(0, 0, size.x, size.y);
}

void Charactor::update() {}

void Charactor::draw() {
    glClearColor(0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    tex1.Draw(mainWindow, {100, 150});
}
