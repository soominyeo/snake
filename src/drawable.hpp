#pragma once

namespace snake {
    class Drawable
    {
        public:
            Drawable();
            Drawable(int y, int x, char ch);

            int getX();
            int getY();
            void setX(int x);
            void setY(int y);
            char getIcon();

        protected:
            int y, x;
            char icon;
    };
}