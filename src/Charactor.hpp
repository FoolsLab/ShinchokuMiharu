#pragma once

#include "common/Texture.hpp"
#include "common/Window.hpp"
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
    void draw();
};
