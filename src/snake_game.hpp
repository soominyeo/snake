#pragma once
#include <ncurses.h>
#include "snake.hpp"
#include "board.hpp"
#include "item.hpp"
#include "missionboard.hpp"

namespace snake{
class SnakeGame
{
public:
    // 생성자 호출 시 게임 창을 stage 0번으로 초기화
    SnakeGame();

    // 소멸자 호출 시 동적으로 할당했던 변수 delete
    ~SnakeGame();

    // 게임 시작할 시(= 생성자 호출 될 시) 진행하는 로직
    void initialize(int stageNum);

    // 사과 만드는 함수
    void createApple();

    // 폭탄 만드는 함수
    void createBomb();

    // 입력 받은 값에 따라 작동을 달리하는 로직
    void getInputState();

    // 게임을 플레이하는 동안 진행하는 로직
    void playingState();

    // 뱀이 다음 위치로 어떻게 나아가야하는지 icon에 따라 조종하는 함수
    void handleNext(SnakePiece next);

    // 사과를 없애는(=먹는) 함수
    void eatApple();

    // 폭탄를 없애는(=먹는) 함수
    void eatBomb();

    // stage 번호에 따라서 게임 창을 초기화하는 함수
    void setStage(int stageNum);

    // 현재 게임이 스테이지 몇인지 get하는 함수
    int getStageNum();

    // 게임 오버 됐는지 확인하는 함수
    bool isOver();

    // 게임 새로고침
    void redraw();

    // ==혜인님 코드 (일정 시간 지나면 아이템 업데이트 기능)==
    //item update per 7seconds
    void ItemUpdate();
    // =============================================

    // 아이템 카운터체크
    int apple_counter=0; 
    int bomb_counter=0; 
    // int warp_counter=0;

    // 아이템 카운터 반환 함수
    int get_apple_Counter()  { return apple_counter; }
    int get_bomb_Counter()  { return bomb_counter; }
    // int get_warp_Counter()  { return warp_counter; }

private:
    Board board;
    Snake snake;
    MissionBoard missionboard;
    bool game_over = false;

    Apple *apple;
    Bomb *bomb;
    // Warp1 *warp1;
    // Warp2 *warp2;

    // Apple 과 Bomb이 동적으로 할당하여서 아이템먹어도 횟수가 업데이트 되지않음
    // 그래서 snake_game.hpp에 item 변수 생성
    
    

};
}