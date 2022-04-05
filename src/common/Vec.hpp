#pragma once

template <class T> struct Vec2 {
    T x, y;
    bool operator==(Vec2 &o) const { return x == o.x && y == o.y; }
    bool operator!=(Vec2 &o) const { return !((*this) != o); }

    Vec2() : x(0), y(0) {}
    Vec2(T _x, T _y) : x(_x), y(_y) {}
    template <class T2> Vec2(const Vec2<T2> &o) {
        x = T(o.x);
        y = T(o.y);
    }

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
