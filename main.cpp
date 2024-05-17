#include <iostream>
#include <ncurses.h>
#include "src/Board.hpp"
#include "src/SnakeGame.hpp"


const int BOARD_SIZE{21};
const double BOARD_ROW{BOARD_SIZE};
const double BOARD_COL{BOARD_SIZE * 3};



int main(){
    initscr();      // start curses mode / window named stdscr memorization
    refresh();      // print it on to the real screen

    noecho();       // no print it user's input char on to the screen

    curs_set(0);

    SnakeGame game = SnakeGame(BOARD_ROW, BOARD_COL);

    while (!game.isOver())
    {
        // 1: get input from user
        game.processInput();

        // 2: update game state
        game.updateState();

        // 3: redraw display
        game.redraw();

        // 4: go to 1, unless game over
    }
    

     getch();        // wait for user input
    endwin();       // end curses mode

    std::cout << "Game Over" << std::endl;

    return 0;
}