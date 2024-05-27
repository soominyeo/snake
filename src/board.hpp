#pragma once
#include <ncurses.h>
#include <stdlib.h>

namespace snake{

    class Board
    {
    public:
        // 생성자 호출하면 21 21 크기의 gameBoard 만듬
        Board();

        // 초기화 함수
        void initialize(int num);

        // gameBoard의 메모리상에서 (y, x) 위치에 ch 문자 추가하기
        void add(int y, int x, char ch);

        // gameBoard의 (y, x) 위치에서의 문자 값 get하기
        char getCharAt(int y, int x);

        // 입력 값 get하기
        char getInput();

        // 현재 게임의 stage 번호 get하기
        int getStageNum();

        // 게임 속도 조절하기
        void setTimeout(int tick);

        // gameBoard 새로고침
        void refresh();

        // 아이템 놓을 수 있는 위치 찾기
        void getItemPos(int &y, int &x);

        void getWarpPos(int &y, int &x);

    private:
        void construct(int height, int width);
        int xMax, yMax;
        WINDOW *gameBoard;
        int stageNum;
    };
}