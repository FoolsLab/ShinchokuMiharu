#pragma once

#include "SysInterface.hpp"
#include "Text.hpp"

class Charactor {
  private:
    IWindow& mainWindow;
    const ICursor& cursor;
    const IMonitorManager& monitors;
    Texture tex1, font1, font2;
    MisakiFont font;

    void setWindowPos(Point);
    void setWindowSize(Size);

  public:
    Charactor(IWindow& _mainWindow, const ICursor& _cursor, const IMonitorManager& _monitorManager);
    ~Charactor();

    void update();
};
