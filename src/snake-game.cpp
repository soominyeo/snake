#include <ncurses.h>
// add time and stdlib libraries
#include <time.h>
#include <stdlib.h>
#include "snake-game.hpp"

namespace snake {
    void SnakeGame::handleNextPiece(SnakePiece next)
    {
        // if apple is existed on screen
        // and the apple is not at the position snake will go to
        // process logic for snake just move
        if (apple != NULL)
        {
            switch (board.getCharAt(next.getY(), next.getX()))
            {
                case 'A':
                    eatApple();
                    break;
                case 'B':
                {
                    eatBomb();

                    // print empty space at the position of snake's tail
                    int emptyRow = snake.tail().getY();
                    int emptyCol = snake.tail().getX();
                    board.add(Empty(emptyRow,emptyCol));

                    // and remove snake's tail
                    snake.removePiece();
                    
                }
                case ' ':
                {
                    // print empty space at the position of snake's tail
                    int emptyRow = snake.tail().getY();
                    int emptyCol = snake.tail().getX();
                    board.add(Empty(emptyRow,emptyCol));

                    // and remove snake's tail
                    snake.removePiece();
                    break;
                }
                
                case '1':
                    game_over = true;
                    break;
                
                default:
                    game_over = true;
                    break;
            }
        }
        
        // print snake piece
        board.add(next);
            
        // add next to front of snake queue
        snake.addPiece(next);
    }

    void SnakeGame::handleWarp(SnakePiece next) {}

    void SnakeGame::createApple()
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        apple = new Apple(y, x);
        board.add(*apple);
    }

    void SnakeGame::createBomb()
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        bomb = new Bomb(y, x);
        board.add(*bomb);
    }

    void SnakeGame::createWarp()
    {
        int y, x;
        board.getWallCoordinates(y, x);
        warp1 = new Warp1(y, x);
        board.add(*warp1);
        board.getEmptyCoordinates(y, x);
        warp2 = new Warp2(y, x);
        board.add(*warp2);
    }

    void SnakeGame::eatApple()
    {  
        delete apple;
        apple = NULL;

        score += 100;
        scoreboard.updateScore(score); 
    }

    void SnakeGame::eatBomb()
    {
        delete bomb;
        bomb = NULL;

        score -= 100;
        scoreboard.updateScore(score);
    }

    // will create board size height * width and initialize
    SnakeGame::SnakeGame(int height, int width)
    {
        board = Board(height, width);

        int sb_row = board.getStartRow() + height;
        int sb_col = board.getStartCol();
        scoreboard = Scoreboard(width, sb_row, sb_col);
        initialize();
    }

    SnakeGame::~SnakeGame()
    {
        delete apple;
        delete bomb;
        delete warp1;
        delete warp2;
    }

    void SnakeGame::initialize()
    {
        apple = NULL;
        bomb = NULL;
        warp1 = NULL;
        warp2 = NULL;
        board.initialize();

        score = 0;
        scoreboard.initialize(score);

        game_over = false;
        // time random seed
        srand(time(NULL));

        // snake's default direction is down
        snake.setDirection(down);

        handleNextPiece(SnakePiece(1, 1));
        handleNextPiece(snake.nexthead());
        handleNextPiece(snake.nexthead());

        snake.setDirection(right);

        handleNextPiece(snake.nexthead());

        // create apple in initialize step
        if (apple == NULL)
        {
            createApple();
        }

        if (bomb == NULL)
        {
            createBomb();
        }

        if (warp1 == NULL && warp2 == NULL)
        {
            createWarp();
        }
    }

    void SnakeGame::processInput()
    {
        char input = board.getInput();
        // process input

        switch (input)
        {
            // case KEY_UP:
            case 'w':
                if (!snake.setDirection(up))
                    game_over = true;
                break;
            case 's':
                if (!snake.setDirection(down))
                    game_over = true;
                break;
            case 'd':
                if (!snake.setDirection(right))
                    game_over = true;
                break;
            case 'a':
                if (!snake.setDirection(left))
                    game_over = true;
                break;
            case 'p':
            board.setTimeout(-1);
                while (board.getInput() != 'p')
                    ;
                board.setTimeout(300);
                break;

        }
    }

    void SnakeGame::updateState()
    {
        //update state

        // create drawable snake piece object it has y, x position snake will go to
        SnakePiece next = snake.nexthead();

        
        if (board.getCharAt(next.getY(), next.getX()) != '@' && board.getCharAt(next.getY(), next.getX()) != '$')
        {
            handleNextPiece(next);
        }

        // @를 만났다면
        else if (board.getCharAt(next.getY(), next.getX()) == '@')
        {
            
            // 빠져나올 $의 위치 저장
            int row = warp2->getY();
            int col = warp2->getX();

            // snake의 현재 방향에 맞추어 next를 설정
            switch (snake.getDirection())
            {
                case up:
                    next = SnakePiece(row-1, col);
                    break;
                case down:
                    next = SnakePiece(row+1, col);
                    break;
                case right:
                    next = SnakePiece(row, col+1);
                    break;
                case left:
                    next = SnakePiece(row, col-1);
                    break;
            }
            handleNextPiece(next);

            // 워프 타자마자 워프 아이콘 삭제
            board.addAt(warp1->getY(), warp1->getX(), '1');
            delete warp1;
            warp1 = NULL;
            board.addAt(warp2->getY(), warp2->getX(), ' ');
            delete warp2;
            warp2 = NULL;
            
        }
        
        // $을 만났다면
        else
        {
            // 빠져나올 @의 위치 저장   
            int row = warp1->getY();
            int col = warp1->getX();

            // @에서 어느 방향으로 빠져나갈 수 있는지 저장하는 변수
            char direction;

            // @에서 빠져나갈 수 있는 방향 찾아 direction에 저장
            if (board.getCharAt(row-1, col) == ' ')
                direction = 'u';
            
            if (board.getCharAt(row+1, col) == ' ')
                direction = 'd';
            
            if (board.getCharAt(row, col-1) == ' ')
                direction = 'l';

            if (board.getCharAt(row, col+1) == ' ')
                direction = 'r';

            // direction의 방향에 따라 snake의 방향 설정과 next 설정
            switch (direction)
            {
                case 'u':
                {
                    snake.doSetDirection(up);
                    next = SnakePiece(row-1, col);
                    break;
                }

                case 'd':
                {
                    snake.doSetDirection(down);
                    next = SnakePiece(row+1, col);
                    break;
                }

                case 'l':
                {
                    snake.doSetDirection(left);
                    next = SnakePiece(row, col-1);
                    break;
                }

                case 'r':
                {
                    snake.doSetDirection(right);
                    next = SnakePiece(row, col+1);
                    break;
                }
            }

            handleNextPiece(next);
            
            // 워프 타자마자 워프 아이콘 삭제
            board.addAt(warp1->getY(), warp1->getX(), '1');
            delete warp1;
            warp1 = NULL;
            board.addAt(warp2->getY(), warp2->getX(), ' ');
            delete warp2;
            warp2 = NULL;
            
        }

        if (score < 0)
        {
            game_over = true;
        }

        // if apple object is not in screen
        if (apple == NULL)
        {
            createApple();
        }
        
        if (bomb == NULL)
        {
            createBomb();
        }

        if (warp1 == NULL && warp2 == NULL)
        {
            createWarp();
        }
    }

    //item update per 7seconds
    void SnakeGame::ItemUpdate()
    {
        if (apple != NULL) {
            board.addAt(apple->getY(), apple->getX(), ' ');
            delete apple;
            apple = NULL;
            createApple();
        }

        if (bomb != NULL) {
            board.addAt(bomb->getY(), bomb->getX(), ' ');
            delete bomb;
            bomb = NULL;
            createBomb();
        }
    }

    void SnakeGame::redraw()
    {
        board.refresh();
        scoreboard.refresh();
    }

    bool SnakeGame::isOver()
    {
        return game_over;
    }

    int SnakeGame::getScore()
    {
        return score;
    }
}