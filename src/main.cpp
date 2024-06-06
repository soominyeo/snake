#include <ncurses.h>
#include "snake_game.hpp"
#include "leaderboard.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <algorithm>

using namespace snake;
int main()
{   
    // before game begins
    std::string name;
    std::cout << "please enter your name:";
    std::cin >> name;

    name.erase(std::remove(name.begin(), name.end(), LeaderBoard::delimiter), name.end());

    // ncurses 시작
    initscr();
    // 일단 초기화 진행
    refresh();
    // 입력된 키 표시 안함
    noecho();
    // 커서 안보이게 설정
    curs_set(0);

    // 게임 스테이지 저장하는 변수
    int stage = 0;

    // 게임 스타트
    SnakeGame game(stage);
    LeaderBoard leaderBoard;
    leaderBoard.init();

    // 게임 무한 반복
    while (true)
    {   
        
        // ==혜인님 코드 (일정 시간 지나면 아이템 업데이트 기능)==
        // 시작 시간 구함
        auto start_time = std::chrono::steady_clock::now();
        // =============================================

        // 게임 오버가 될 때까지
        while (!game.isOver())
        {   
            // stage는 현 게임의 스테이지를 계속 업데이트
            stage = game.getStageNum();
            
            // 몇 스테이지인지 출력
            switch (stage)
            {
            case 0:
                mvprintw(0, 0, "Stage 1");
                refresh();
                break;
            case 1:
                mvprintw(0, 0, "Stage 2");
                refresh();
                break;
            case 2:
                mvprintw(0, 0, "Stage 3");
                refresh();
                break;
            case 3:
                mvprintw(0, 0, "Last Stage!");
                refresh();
                break;
            
            default:
                mvprintw(0, 0, "***Bonus Stage***");
                refresh();
                break;
            }
            
            // 게임에서 입력 값에 따라 바뀌는 로직
            game.getInputState();

            // 게임하는 중 진행되는 로직
            game.playingState();

            // 게임 새로고침(= 실제로 창에 표시하는 단계)
            game.redraw();

            // ==혜인님 코드 (일정 시간 지나면 아이템 업데이트 기능)==
            //특정 시간 구함
            auto end_time = std::chrono::steady_clock::now();

            //시간 계산(특정 시간 - 시작 시간)
            auto temp= std::chrono::duration_cast<std::chrono::seconds>(end_time-start_time).count();
            
            //7초가 됐을 때
            if(temp>=7){
                game.ItemUpdate();
                start_time=end_time;
            }
            // ==============================================
        }
        // 게임 오버가 되면 창 클리어하고 안내 메세지 출력
        clear();
        leaderBoard.load();
        leaderBoard.addRank(Rank(name, game.score));
        leaderBoard.save();
        leaderBoard.show();
        mvprintw(getmaxy(stdscr)-2, 0, "Game Over!!! (score: %d)", game.score); 
        mvprintw(getmaxy(stdscr)-1, 0, "Do You Want Quit? [q] / Restart: [Press Any Key]");


        // 만약 q를 눌렀으면 while문 빠져 나간다
        char ch = getch();
        if (ch == 'q')
        {
            break;
        }
        // 다른 키를 눌렀으면 게임 오버된 스테이지로 초기화하고 score 0점으로 게임 진행
        clear();
        game.score = 0;
        game.setGameOver(false);
        stage = game.getStageNum();
        game.initialize(stage);
    }
    
    
    // ncurses 종료
    endwin();
}