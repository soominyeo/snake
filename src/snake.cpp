#include <queue>
#include "snake.hpp"

SnakePiece::SnakePiece()
{
    this->x = this->y = 0;
    this->icon = '#';
}

SnakePiece::SnakePiece(int y, int x)
{
    this->x = x;
    this->y = y;
    this->icon = '#';
}

Snake::Snake()
{
    cur_direction = down;
}

void Snake::addPiece(SnakePiece piece)
{
    prev_pieces.push(piece);
}

void Snake::removePiece()
{
    prev_pieces.pop();
}

SnakePiece Snake::tail()
{
    return prev_pieces.front();
}

SnakePiece Snake::head()
{
    return prev_pieces.back();
}

Direction Snake::getDirection()
{
    return cur_direction;
}

bool Snake::setDirection(Direction d)
{
    if (cur_direction + d != 0)
    {
        cur_direction = d;
        return true;
    }
    return false;
}

void Snake::doSetDirection(Direction d)
{
    cur_direction = d;
}

// return drawable snake's piece object that snake will go to the next
SnakePiece Snake::nexthead()
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