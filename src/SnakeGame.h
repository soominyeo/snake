#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "Board.hpp"
#include "Empty.hpp"
#include "Apple.hpp"
#include "Bomb.hpp"
#include "Drawable.hpp"
#include "Snake.hpp"
#include "Scoreboard.hpp"

class SnakeGame
{
private:
    Board board;
    bool game_over;
    Apple *apple;
    Bomb *bomb;
    Snake snake;
    Scoreboard scoreboard;
    int score;
    int length;

    void handleNextPiece(SnakePiece next)
    {
        if(apple != NULL || bomb !=NULL){
            switch(board.getCharAt(next.getY(), next.getX())){
            case 'B':
            {
                eatBomb();
                if(length<3)
                    game_over=true;
                else{
                    int tmpRow= snake.tail().getY();
                    int tmpCol= snake.tail().getX();
                    board.add(Empty(tmpRow, tmpCol));
                    snake.removePiece();
                }
                break;
            }
            case 'A':
            {
                eatApple();
                snake.addPiece(next);
                break;
            }
            case ' ':
            {
                int emptyRow= snake.tail().getY();
                int emptyCol= snake.tail().getX();
                board.add(Empty(emptyRow,emptyCol));
                snake.removePiece();
                snake.addPiece(next);
                break;
            }
            default:
            {
                game_over = true;
                break;
            }
            }
        }
        board.add(next);
    }

    void eatApple()
    {
        delete apple;
        apple = NULL;
        score +=100;
        length+=1;
        scoreboard.updateScore(score);
    }

    void eatBomb()
    {
        delete bomb;
        bomb = NULL;
        length-=1;
    }

    void createApple()
    {
        int y,x;
        board.getEmptycoordinate(y,x); //공백인 좌표 얻음
        apple= new Apple(y,x); //새로운 apple 생성
        board.add(*apple);
    }

    void createBomb()
    {
        int y,x;
        board. getEmptycoordinate(y,x);
        bomb= new Bomb(y,x);
        board.add(*bomb);
    }

public:
    SnakeGame(int height, int width, int speed) : board(height,width, speed) //초기화리스트
    {
        int sb_row  = board.getStartRow()+height;
        int sb_col= board.getStartCol();
        scoreboard= Scoreboard(width, sb_row, sb_col);
        initialize();
    }
    
    ~SnakeGame()
    {
        delete apple;
        apple = NULL;
        delete bomb;
        bomb = NULL;
    }
    
    void initialize()
    {
        length=3;
        bomb=NULL;
        apple =NULL;
        board.initialize();
        game_over=false;

        //점수판
        score=0;
        scoreboard.initialize(score);

        srand(time(NULL));
        snake.setDirection(Direction::down);

        handleNextPiece(SnakePiece(1,1));
        handleNextPiece(snake.nextHead());
        snake.setDirection(Direction::right);
        handleNextPiece(snake.nextHead());

        if(apple==NULL)
            createApple();
        if(bomb==NULL)
            createBomb();
    }

    //process input
    void Input()
    {
        chtype input=board.getInput();
        int old_timeout=board.getTimeout();
        //방향키 설정
        switch(input) 
        {
            //case KEY_UP: //방향키용
            case 'w': //wasd용 //up
                snake.setDirection(Direction::up);
                break;
            case 's': //down
                snake.setDirection(Direction::down);
                break;
            case 'd': //right
                snake.setDirection(Direction::right);
                break;
            case 'a': //left
                snake.setDirection(Direction::left);
                break;
            case 'p': //일시정지
                board.setTimeout(-1);
                while (board.getInput()!='p');
                board.setTimeout(old_timeout);
            default:
                break;
        }
    }

    void UpdateState()
    {
        handleNextPiece(snake.nextHead());

       if(apple==NULL)
            createApple();

        if(bomb ==NULL)
            createBomb();
    }

    void redraw()
    {  
        board.refresh();
        scoreboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

    int getScore()
    {
        return score;
    }
};
