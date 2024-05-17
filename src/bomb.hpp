#pragma once
#include "drawable.hpp"

namespace snake {
    class Bomb : public Drawable
    {
    public:
        Bomb(int y, int x);
    };
}