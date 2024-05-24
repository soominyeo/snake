#pragma once
#include "drawable.hpp"
#include "apple.hpp"
#include "bomb.hpp"
#include "warp1.hpp"
#include "warp2.hpp"
#include "empty.hpp"
#include "board.hpp"
#include "scoreboard.hpp"
#include "snake.hpp"


namespace snake {
    class SnakeGame
    {
    private:
        Board board;
        bool game_over;
        Apple *apple;
        Bomb *bomb;
        Warp1 *warp1;
        Warp2 *warp2;
        Snake snake;
        Scoreboard scoreboard;
        int score;

        void handleNextPiece(SnakePiece next);
        void handleWarp(SnakePiece next);
        void createApple();
        void createBomb();
        void createWarp();
        void eatApple();
        void eatBomb();
        

    public:
        // will create board size height * width and initialize
        SnakeGame(int height, int width);
        ~SnakeGame();
        void initialize();
        void processInput();
        void updateState();
        //new
        void ItemUpdate();
        void redraw();
        bool isOver();
        int getScore();

    };
}