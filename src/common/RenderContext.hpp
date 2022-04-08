#pragma once

#include "Texture.hpp"
#include <utility>

template <class FTEndCallback> class RenderContext {
    FTEndCallback endCB;
    bool invalid;
    Size viewportSize;

  public:
    RenderContext(Size viewportSize, FTEndCallback callback)
        : viewportSize(viewportSize), endCB(std::move(callback)),
          invalid(false) {}
    RenderContext(RenderContext &&c)
        : endCB(std::move(c.endCB)), invalid(c.invalid) {
        c.invalid = true;
    }
    ~RenderContext() {
        if (!invalid) {
            endCB();
            invalid = true;
        }
    }

    void Draw(const Texture &tex, Point dstPos) const {
        tex.Draw(viewportSize, dstPos);
    }
    void Draw(const Texture &tex, const Point dstPos, const Point srcPos,
              const Size srcRect) const {
        tex.Draw(viewportSize, dstPos, srcPos, srcRect);
    }
};
