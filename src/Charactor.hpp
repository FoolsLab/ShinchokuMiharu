#pragma once

#include "utils/Texture.hpp"

class Charactor {
  private:
    Texture tex1;

  public:
    Charactor();
    ~Charactor();

    void update();
    void draw();
};
