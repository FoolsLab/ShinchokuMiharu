#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stb_image.h>

#include <vector>

template <class T> struct Vec2 {
    T x, y;
    bool operator==(Vec2 &o) const { return x == o.x && y == o.y; }
    bool operator!=(Vec2 &o) const { return !((*this) != o); }

    template <class T2> Vec2<T> &operator=(const Vec2<T2> &o) {
        x = T(o.x);
        y = T(o.y);
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
};

class MonitorManager {
    std::vector<Monitor> monitors;

  public:
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
        Vec2<double> tmpCPos;
        Vec2<int> tmpWPos;
        glfwGetCursorPos(window, &tmpCPos.x, &tmpCPos.y);
        glfwGetWindowPos(window, &tmpWPos.x, &tmpWPos.y);
        wPos = tmpWPos;
    }

    void setWindowPos(Point newPos) {
        glfwSetWindowPos(window, newPos.x, newPos.y);
        wPos = newPos;
    }
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
