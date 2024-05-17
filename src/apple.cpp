
#include <ncurses.h>
#include "apple.hpp"


Apple::Apple(int y, int x) {
    this->y = y;
    this->x = x;
    this-> icon = 'A';
}