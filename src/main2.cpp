#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "board.hpp"
#include "snake-game.hpp"


const int BOARD_SIZE{21};
const double BOARD_ROW{BOARD_SIZE};
const double BOARD_COL{BOARD_SIZE * 3};

using namespace snake;

int main(){
    initscr();      // start curses mode / window named stdscr memorization
    refresh();      // print it on to the real screen

    noecho();       // no print it user's input char on to the screen

    curs_set(0);

    SnakeGame game = SnakeGame(BOARD_ROW, BOARD_COL);

    //시작 시간 구함	
    auto start_time = std::chrono::steady_clock::now();

    while (!game.isOver())
    {
        // 1: get input from user
        game.processInput();
        // 2: update game state
        game.updateState();
        // 3: redraw display
        game.redraw();
        
        //특정 시간 구함
        auto end_time = std::chrono::steady_clock::now();
        //시간 계산(특정 시간 - 시작 시간)
        auto temp= std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time).count();
        
        //7초가 됐을 때
        if(temp>=7){
            game.ItemUpdate();
            start_time=end_time;
        }
        // 4: go to 1, unless game over
    }
    

     getch();        // wait for user input
    endwin();       // end curses mode

    std::cout << "Game Over" << std::endl;

    return 0;
}