#include "Charactor.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>

Charactor::Charactor(IWindow& _mainWindow, const ICursor& _cursor, const IMonitorManager& _monitorManager)
    : mainWindow(_mainWindow), cursor(_cursor), monitors(_monitorManager),
      tex1("./assets/test.png"),
      font1("./assets/k8x12_jisx0201.png", GL_NEAREST),
      font2("./assets/k8x12_jisx0208.png", GL_NEAREST) {
    setWindowSize({512, 512});
}

Charactor::~Charactor() {}

void Charactor::setWindowPos(Point pos) { mainWindow.setWindowPos(pos); }

void Charactor::setWindowSize(Size size) {
    mainWindow.setWindowSize(size);
    glViewport(0, 0, size.x, size.y);
}

void Charactor::update() {
    auto context = mainWindow.renderBegin();

    glClearColor(0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    context->Draw(font2, cursor.getPos(), {0, 0}, {100, 100}, 2.0f);
}
