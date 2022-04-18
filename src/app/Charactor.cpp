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

    // auto str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    auto str = "祇園精舎の鐘の声、諸行無常の響きあり。娑羅双樹の花の色、盛者必衰の理をあらはす。奢れる人も久しからず、ただ春の夜の夢のごとし。猛き者もつひにはほろびぬ、ひとへに風の前の塵に同じ。";

    font.Draw(*context.get(), cursor.getPos(), {300, 300}, 3.0f, str);
}
