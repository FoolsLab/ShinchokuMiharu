#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <stb_image.h>

#include <vector>

template <class T> struct Vec2 {
    T x, y;
    bool operator==(Vec2 &o) { return x == o.x && y == o.y; }
    bool operator!=(Vec2 &o) { return !((*this) != o); }
};

using Point = Vec2<float>;
using Size = Vec2<float>;
using Scale = Vec2<float>;

struct Monitor {
    Point origin;
    Size size;
    Scale scale;
    bool isCoordInMonitor(Point pos) const {
        return origin.x <= pos.x && pos.x < origin.x + size.x &&
               origin.y <= pos.y && pos.y < origin.y + size.y;
    }
};

class MonitorManager {
    std::vector<Monitor> monitors;

  public:
    int getMonitorIndexFromCoord(Point pos) const {
        for (int i = 0; const auto &monitor : monitors) {
            if (monitor.isCoordInMonitor(pos)) {
                return i;
            }
            i++;
        }
        return -1;
    }
};

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
