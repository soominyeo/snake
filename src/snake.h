#pragma once
#include <ncurses.h>
#include <queue>
#include "Drawable.hpp"

enum Direction
{
    up= -1,
    down =1,
    left =-2,
    right=2
};

class SnakePiece: public Drawable
{
public:
    SnakePiece()
    {
        this->x = this->y = 0;
        this->icon= '#';
    }

    SnakePiece(int y, int x)
    {
        this->x = x;
        this->y = y;
        this->icon='#';
    }
};

class Snake
{
    std::queue<SnakePiece> prev_pieces;
    Direction cur_direction;
public:
    Snake()
    {
        cur_direction =Direction::down; //변경
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

    void setDirection(Direction d)
    {
        if(cur_direction + d != 0){
            cur_direction=d;
        }
    }

    SnakePiece nextHead()
    {
        int row = head().getY();
        int col= head().getX();

        switch(cur_direction)
        {
            case Direction::down:
                row++;
                break;
            case Direction::up:
                row--;
                break;
            case Direction::left:
                col--;
                break;
            case Direction::right:
                col++;
                break;
        }
        return SnakePiece(row,col);
    }
};
