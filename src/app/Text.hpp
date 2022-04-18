#pragma once

#include "SysInterface.hpp"
#include "Texture.hpp"
#include <string>

class Font {
  public:
    virtual bool Draw(IRenderContext& ctx, Point pos, Size rect, float fontsize,
                      std::string str) const = 0;
};

class MisakiFont : public Font {
    Texture img201, img208;
  public:
    MisakiFont();
    bool Draw(IRenderContext& ctx, Point pos, Size rect, float fontsize,
              std::string str) const override;
};
