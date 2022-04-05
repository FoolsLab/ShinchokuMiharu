#pragma once

#include "common/Window.hpp"
#include "utils/Texture.hpp"
#include <memory>

class Charactor {
  private:
    const Window *mainWindow;
    Texture tex1;

    void setWindowPos(Point);
    void setWindowSize(Size);
  public:
    Charactor(const Window *_mainWindow);
    ~Charactor();

    void update();
    void draw();
};
