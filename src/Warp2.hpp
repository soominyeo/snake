#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Warp2 : public Drawable
{
public:
    Warp2(int y, int x)
    {
        this->y = y;
        this->x = x;
        this-> icon = '$';
    }
};