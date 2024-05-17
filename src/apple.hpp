#pragma once
#include "drawable.hpp"

namespace snake {
    class Apple : public Drawable
    {
    public:
        Apple(int y, int x);
    };
}