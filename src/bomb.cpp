#include "bomb.hpp"

namespace snake {
    Bomb::Bomb(int y, int x)
    {
        this->y = y;
        this->x = x;
        this-> icon = 'B';
    }
}