#pragma once
#include <ncurses.h>

namespace snake{
class Item
{
public:
    Item(int y = 0, int x = 0) : row(y), col(x), icon(' ') {}

    int getX()
    {
        return col;
    }

    int getY()
    {
        return row;
    }

    void setIcon(char ch)
    {
        icon = ch;
    }    

protected:
    int row, col;
    char icon;
};

class Apple : public Item
{
public:
    Apple(int y = 0, int x = 0) : Item(y, x)
    {
        icon = 'A';
    }
};

class Bomb : public Item
{
public:
    Bomb(int y = 0, int x = 0) : Item(y, x)
    {
        icon = 'B';
    }
};
}