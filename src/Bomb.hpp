#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Bomb : public Drawable
{
public:
    Bomb(int y, int x)
    {
        this->y = y;
        this->x = x;
        this-> icon = 'B';
    }
};