#pragma once

class Drawable
{
    public:
        Drawable(){
            y = x = 0;
            icon = ' ';
        }

        Drawable(int y, int x, char ch)
        {
            this-> y = y;
            this-> x = x;
            this-> icon = ch;
        }

        int getX()
        {
            return x;
        }

        int getY()
        {
            return y;
        }

        void setX(int x)
        {
            this-> x = x;
        }

        void setY(int y)
        {
            this-> y = y;
        }

        char getIcon()
        {
            return icon;
        }
    protected:
        int y, x;
        char icon;
};