#pragma once
#include "drawable.hpp"

class Board{
    public:
    Board();
    Board(int height, int width);

    // initialize function
    void initialize();

    // create board's sideline
    void addBorder();

    // print drawable object on screen 
    void add(Drawable drawable);

    // print ch on board_win at (y, x)
    void addAt(int y, int x, char ch);

    // on screen, get input value
    char getInput();

    // get empty space's direction y, x
    void getEmptyCoordinates(int &y, int &x);

    // '1'인 벽 위치 가지기
    void getWallCoordinates(int &y, int &x);
    
    // return char at the position y, x on screen
    char getCharAt(int y, int x);

    // board clear
    void clear();

    // print board
    void refresh();

    void setTimeout(int timeout);

    int getStartRow();

    int getStartCol();

private:
    WINDOW *board_win;
    int height, width;
    int start_row, start_col;

    void construct(int height, int width);
};