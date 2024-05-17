#pragma once
#include "drawable.hpp"

namespace snake {
    class Empty : public Drawable
    {
    public:
        Empty(int y, int x);
    };
}