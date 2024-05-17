#include <ncurses.h>
#include <stdlib.h>
#include "board.hpp"

Board::Board() {
    construct(0, 0);
}

Board::Board(int height, int width){
    construct(height, width);    
}


void Board::initialize() {
    // board clear and print
    clear();
    mvwaddch(board_win, 0, 0, '2');
    mvwaddch(board_win, 0, this->width-1, '2');
    mvwaddch(board_win, this->height-1, 0, '2');
    mvwaddch(board_win, this->height-1, this->width-1, '2');

    for (int i = 1; i < this->width-1; i++)
    {
        mvwaddch(board_win, 0, i, '1');
        mvwaddch(board_win, this->height-1, i, '1');
    }

    for (int i = 1; i < this->height-1; i++)
    {
        mvwaddch(board_win, i, 0, '1');
        mvwaddch(board_win, i, this->width-1, '1');
    }
}

void Board::addBorder(){
    box(board_win, 0, 0);
}

void Board::add(Drawable drawable)
{
    addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
}

void Board::addAt(int y, int x, char ch){
    mvwaddch(board_win, y, x, ch);
}

char Board::getInput(){
    return wgetch(board_win);
}

void Board::getEmptyCoordinates(int &y, int &x)
{   
    // rand() % height means get a random value between 0 to height 
    while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');
}

void Board::getWallCoordinates(int &y, int &x)
{
    while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != '1');
}

char Board::getCharAt(int y, int x)
{
    return mvwinch(board_win, y, x);
}

void Board::clear(){
    wclear(board_win);
    addBorder();
}

void Board::refresh(){
    wrefresh(board_win);
}

void Board::setTimeout(int timeout)
{
    wtimeout(board_win, timeout);
}

int Board::getStartRow()
{
    return start_row;
}

int Board::getStartCol()
{
    return start_col;
}

void Board::construct(int height, int width){
    // set height, width value and create board with them
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);       // get stdscr's height, width
    this->height = height;
    this->width = width;

    start_row = (yMax/2) - (height/2);
    start_col = (xMax/2) - (width/2);

    // create board at stdscr's middle
    board_win = newwin(height, width, start_row, start_col);
    

    
    wtimeout(board_win, 300);

    keypad(board_win, true);
}