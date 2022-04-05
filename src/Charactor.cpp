#include "Charactor.hpp"
#include <GLFW/glfw3.h>
#include <gl/GL.h>

Charactor::Charactor() : tex1("./assets/test.png") {}

Charactor::~Charactor() {}

void Charactor::update() {}

void Charactor::draw() {
    tex1.Draw({0,0});
}
