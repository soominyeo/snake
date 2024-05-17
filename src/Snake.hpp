#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include <queue>



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
    SnakePiece()
    {
        this->x = this->y = 0;
        this->icon = '#';
    }

    SnakePiece(int y, int x)
    {
        this->x = x;
        this->y = y;
        this->icon = '#';
    }

    
};

class Snake
{
    std::queue<SnakePiece> prev_pieces;
    Direction cur_direction;

public:
    Snake()
    {
        cur_direction = down;
    }

    void addPiece(SnakePiece piece)
    {
        prev_pieces.push(piece);
    }

    void removePiece()
    {
        prev_pieces.pop();
    }

    SnakePiece tail()
    {
        return prev_pieces.front();
    }

    SnakePiece head()
    {
        return prev_pieces.back();
    }

    Direction getDirection()
    {
        return cur_direction;
    }

    bool setDirection(Direction d)
    {
        if (cur_direction + d != 0)
        {
            cur_direction = d;
            return true;
        }
        return false;
    }

    void doSetDirection(Direction d)
    {
        cur_direction = d;
    }

    // return drawable snake's piece object that snake will go to the next
    SnakePiece nexthead()
    {
        int row = head().getY();
        int col = head().getX();

        switch (cur_direction)
        {
            case down:
                row++;
                break;
            case up:
                row--;
                break;
            case left:
                col--;
                break;
            case right:
                col++;
                break;
        }

        return SnakePiece(row, col);
    }

};