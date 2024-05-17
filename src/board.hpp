#pragma once
#include <ncurses.h>
#include <stdlib.h>
#include "drawable.hpp"


class Board{
    public:
    Board(){
        construct(0, 0);
    }

    Board(int height, int width){
        construct(height, width);    
    }

    // initialize function
    void initialize(){
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

    // create board's sideline
    void addBorder(){
        box(board_win, 0, 0);
    }

    // print drawable object on screen 
    void add(Drawable drawable)
    {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    // print ch on board_win at (y, x)
    void addAt(int y, int x, char ch){
        mvwaddch(board_win, y, x, ch);
    }

    // on screen, get input value
    char getInput(){
        return wgetch(board_win);
    }

    // get empty space's direction y, x
    void getEmptyCoordinates(int &y, int &x)
    {   
        // rand() % height means get a random value between 0 to height 
        while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');
    }

    // '1'인 벽 위치 가지기
    void getWallCoordinates(int &y, int &x)
    {
        while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != '1');
    }
    
    // return char at the position y, x on screen
    char getCharAt(int y, int x)
    {
        return mvwinch(board_win, y, x);
    }

    // board clear
    void clear(){
        wclear(board_win);
        addBorder();
    }

    // print board
    void refresh(){
        wrefresh(board_win);
    }

    void setTimeout(int timeout)
    {
        wtimeout(board_win, timeout);
    }

    int getStartRow()
    {
        return start_row;
    }

    int getStartCol()
    {
        return start_col;
    }

private:
    WINDOW *board_win;
    int height, width;
    int start_row, start_col;

    // set height, width value and create board with them
    void construct(int height, int width){
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
};