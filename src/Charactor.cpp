#include "Charactor.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>

Charactor::Charactor(Window *const _mainWindow)
    : mainWindow(_mainWindow), tex1("./assets/test.png") {
    setWindowSize({512, 512});
}

Charactor::~Charactor() {}

void Charactor::setWindowPos(Point pos) { mainWindow->setWindowPos(pos); }

void Charactor::setWindowSize(Size size) {
    mainWindow->setWindowSize(size);
    glViewport(0, 0, size.x, size.y);
}

void Charactor::update() {
    auto context = mainWindow->renderBegin();

    glClearColor(0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    context.Draw(tex1, {150, 100});
}

void Charactor::draw() {}
