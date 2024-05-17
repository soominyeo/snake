#pragma once
#include <queue>
#include "drawable.hpp"

namespace snake {
    enum Direction
    {
        up = -1,
        down = 1,
        left = -2,
        right = 2
    };

    class SnakePiece : public Drawable
    {
    public:
        SnakePiece();
        SnakePiece(int y, int x);
    };

    class Snake
    {
        std::queue<SnakePiece> prev_pieces;
        Direction cur_direction;
    public:
        Snake();
        void addPiece(SnakePiece piece);
        void removePiece();
        SnakePiece tail();
        SnakePiece head();
        Direction getDirection();
        bool setDirection(Direction d);
        void doSetDirection(Direction d);
        // return drawable snake's piece object that snake will go to the next
        SnakePiece nexthead();
    };
}