#pragma once

#include "Texture.hpp"
#include <utility>

template <class FTEndCallback> class RenderContext {
    FTEndCallback endCB;
    bool invalid;

  public:
    RenderContext(FTEndCallback callback)
        : endCB(std::move(callback)), invalid(false) {}
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
};
