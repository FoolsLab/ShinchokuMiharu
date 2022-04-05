#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stb_image.h>

#include <vector>

template <class T> struct Vec2 {
    T x, y;
    bool operator==(Vec2 &o) const { return x == o.x && y == o.y; }
    bool operator!=(Vec2 &o) const { return !((*this) != o); }

    Vec2() : x(0), y(0) {}
    Vec2(T _x, T _y) : x(_x), y(_y) {}
    template <class T2> Vec2<T> &operator=(const Vec2<T2> &o) {
        x = T(o.x);
        y = T(o.y);
    }
    template <class T2> Vec2(const Vec2<T2> &o) { (*this) = o; }

    template <class T2> auto &operator+=(const Vec2<T2> &o) {
        x += o.x;
        y += o.y;
        return (*this);
    }
    template <class T2> auto operator+(const Vec2<T2> &o) {
        Vec2<decltype(this->x + o.x)> tmp = (*this);
        tmp += o;
        return tmp;
    }
};

using Point = Vec2<float>;
using Size = Vec2<float>;
using Scale = Vec2<float>;

struct Monitor {
    Point origin;
    Size size;
    Scale scale;
    bool isCoordInMonitor(const Point pos) const {
        return origin.x <= pos.x && pos.x < origin.x + size.x &&
               origin.y <= pos.y && pos.y < origin.y + size.y;
    }

    Monitor(GLFWmonitor *glfwMonitor) {
        const GLFWvidmode *videoMode = glfwGetVideoMode(glfwMonitor);
        size.x = videoMode->width;
        size.y = videoMode->height;

        Vec2<int> tmpPos;
        glfwGetMonitorPos(glfwMonitor, &tmpPos.x, &tmpPos.y);
        origin = tmpPos;

        Vec2<float> tmpScale;
        glfwGetMonitorContentScale(glfwMonitor, &tmpScale.x, &tmpScale.y);
        scale = tmpScale;
    }
};

class MonitorManager {
    std::vector<Monitor> monitors;

  public:
    void update() {
        int count;
        auto pMonitors = glfwGetMonitors(&count);
        monitors.resize(count);
        for (size_t i = 0; i < count; i++) {
            monitors[i] = Monitor(pMonitors[i]);
        }
    }

    int getMonitorIndexFromCoord(const Point pos) const {
        for (int i = 0; const auto &monitor : monitors) {
            if (monitor.isCoordInMonitor(pos)) {
                return i;
            }
            i++;
        }
        return -1;
    }
    auto getMonitorFromCoord(const Point pos) const {
        int index = getMonitorIndexFromCoord(pos);
        if (index == -1) {
            throw std::exception("monitor get error");
        }
        return monitors[index];
    }
    auto getMonitor(const size_t index) const { return monitors[index]; }
};

class Window {
    GLFWwindow *window;

    Point wPos;

  public:
    void update() {
        Vec2<int> tmpWPos;
        glfwGetWindowPos(window, &tmpWPos.x, &tmpWPos.y);
        wPos = tmpWPos;
    }

    auto getCursorPos() const {
        Vec2<double> tmpCPos;
        glfwGetCursorPos(window, &tmpCPos.x, &tmpCPos.y);

        return Point(tmpCPos);
    }

    void setWindowPos(Point newPos) {
        glfwSetWindowPos(window, newPos.x, newPos.y);
        wPos = newPos;
    }
    auto getWindowPos() const { return wPos; }
};

class System {
    Window mainWindow;
    Point cursorPos;

    MonitorManager monitorManager;

    void updateCursourPos() {
        cursorPos = mainWindow.getCursorPos() + mainWindow.getWindowPos();
    }

  public:
    void update() {
        mainWindow.update();
        updateCursourPos();
    }
    auto getCursorPos() const { return cursorPos; }
};

int main(void) {
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
