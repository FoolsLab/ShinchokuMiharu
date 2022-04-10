#pragma once

#include "../sys/Texture.hpp"
#include "../sys/Window.hpp"
#include <memory>

class Charactor {
  private:
    Window *const mainWindow;
    Texture tex1;

    void setWindowPos(Point);
    void setWindowSize(Size);

  public:
    Charactor(Window *const _mainWindow);
    ~Charactor();

    void update();
};
