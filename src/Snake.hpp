#pragma once
#include <ncurses.h>
#include <queue>

namespace snake{
enum Direction
{
    up = -1,
    down = 1,
    left = -2,
    right = 2,
};

class SnakePiece
{
public:
    SnakePiece(int y = 0, int x = 0, char ch = '#') : row(y), col(x), icon(ch) {}

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

private:
    int row, col;
    char icon;
};

class Snake
{
    std::queue<SnakePiece> snake;
    Direction cur_direction;

public:
    Snake()
    {
        cur_direction = right;
    }

    void initialize()
    {
        while (!snake.empty())
        {
            snake.pop();
        }

        snake.push(SnakePiece(1, 1, '#'));
        snake.push(SnakePiece(1, 2, '#'));
        snake.push(SnakePiece(1, 3, '#'));
        snake.push(SnakePiece(1, 4, '@'));

        cur_direction = right;
    }

    void addBody(SnakePiece piece)
    {
        snake.push(piece);
    }

    void removeBody()
    {
        snake.pop();
    }

    SnakePiece tail()
    {
        return snake.front();
    }

    SnakePiece head()
    {
        return snake.back();
    }

    bool setDirection(Direction direct)
    {
        if (cur_direction + direct == 0)
        {
            return false;
        }
        cur_direction = direct;
        return true;
    }

    int getSize()
    {
        return snake.size() - 1;
    }

    Direction getDirection()
    {
        return cur_direction;
    }

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
}