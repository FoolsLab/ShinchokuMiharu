#pragma once

#include "../sys/Texture.hpp"
#include <concepts>
#include <memory>

class IRenderContext {
  public:
    virtual void Draw(const Texture& tex, Point dstPos) const = 0;
    virtual void Draw(const Texture& tex, const Point dstPos,
                      const Point srcPos, const Size srcRect) const = 0;
    virtual ~IRenderContext(){};
};

template <class TRenderContext>
requires std::derived_from<TRenderContext, IRenderContext>
class IWindow {
  public:
    virtual bool CloseRequested() const = 0;

    virtual void setWindowPos(Point newPos) = 0;
    virtual Point getWindowPos() const = 0;

    virtual void setWindowSize(Size newSize) = 0;
    virtual Size getWindowSize() const = 0;

    [[nodiscard]] virtual TRenderContext renderBegin() const = 0;
};

// struct Monitor {
//     Point origin;
//     Size size;
//     Scale scale;
//     bool isCoordInMonitor(const Point pos) const;
// };

// class IMonitorManager {
//   public:
//     [[nodiscard]] virtual int
//     getMonitorIndexFromCoord(const Point pos) const = 0;
//     [[nodiscard]] virtual Monitor&
//     getMonitorFromCoord(const Point pos) const = 0;
//     [[nodiscard]] virtual size_t getMonitorNum() const = 0;
//     [[nodiscard]] virtual Monitor& getMonitor(const size_t index) const = 0;
// };

template <class T> class Charactor {
  private:
    IWindow<T>& mainWindow;
    // IMonitorManager& monitors;
    // IWindow& mainWindow;
    Texture tex1;

    void setWindowPos(Point pos) { mainWindow.setWindowPos(pos); };
    void setWindowSize(Size size) {
        mainWindow.setWindowSize(size);
        glViewport(0, 0, size.x, size.y);
    };

  public:
    Charactor(IWindow<T>& _mainWindow)
        : mainWindow(_mainWindow), tex1("./assets/test.png") {
        setWindowSize({512, 512});
    }
    ~Charactor(){};

    void update() {
        auto context = mainWindow.renderBegin();

        glClearColor(0, 0, 0, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        context.Draw(tex1, {150, 100});
    };
};
