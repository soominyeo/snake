#pragma once
#include <ncurses.h>
#include "drawable.hpp"

class Warp1 : public Drawable
{
public:
    Warp1(int y, int x)
    {
        this->y = y;
        this->x = x;
        this-> icon = '@';
    }
};