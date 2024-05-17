#include "drawable.hpp"

namespace snake {
    Drawable::Drawable() {
        y = x = 0;
        icon = ' ';
    }

    Drawable::Drawable(int y, int x, char ch)
    {
        this-> y = y;
        this-> x = x;
        this-> icon = ch;
    }

    int Drawable::getX()
    {
        return x;
    }

    int Drawable::getY()
    {
        return y;
    }

    void Drawable::setX(int x)
    {
        this-> x = x;
    }

    void Drawable::setY(int y)
    {
        this-> y = y;
    }

    char Drawable::getIcon()
    {
        return icon;
    }
}