#pragma once

#include "../sys/Texture.hpp"
#include <memory>

class IRenderContext {
  public:
    virtual void Draw(const Texture& tex, Point dstPos) const = 0;
    virtual void Draw(const Texture& tex, const Point dstPos,
                      const Point srcPos, const Size srcRect) const = 0;
    virtual void Draw(const Texture& tex, const Point dstPos,
                      const Point srcPos, const Size srcRect,
                      float scale) const = 0;
    virtual ~IRenderContext() {};
};

class IWindow {
  public:
    virtual bool CloseRequested() const = 0;

    virtual void setWindowPos(Point newPos) = 0;
    virtual Point getWindowPos() const = 0;

    virtual void setWindowSize(Size newSize) = 0;
    virtual Size getWindowSize() const = 0;

    [[nodiscard]] virtual std::unique_ptr<IRenderContext> renderBegin() const = 0;
};

class ICursor {
  public:
    virtual Point getPos() const = 0;
};

class IMonitor {
  public:
    virtual bool isCoordInMonitor(const Point pos) const = 0;
};

class IMonitorManager {
  public:
    [[nodiscard]] virtual int getMonitorIndexFromCoord(const Point pos) const = 0;
    [[nodiscard]] virtual const IMonitor& getMonitorFromCoord(const Point pos) const = 0;
    [[nodiscard]] virtual size_t getMonitorNum() const = 0;
    [[nodiscard]] virtual const IMonitor& getMonitor(const size_t index) const = 0;
};

class Charactor {
  private:
    IWindow& mainWindow;
    const ICursor& cursor;
    const IMonitorManager& monitors;
    Texture tex1, font1, font2;

    void setWindowPos(Point);
    void setWindowSize(Size);

  public:
    Charactor(IWindow& _mainWindow, const ICursor& _cursor, const IMonitorManager& _monitorManager);
    ~Charactor();

    void update();
};