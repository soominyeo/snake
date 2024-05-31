#ifndef MISSIONBOARD_HPP
#define MISSIONBOARD_HPP

#include <ncurses.h>
#include <cstdio> 
#include <iostream>
#include <string>
#include "board.hpp"
namespace snake{
class MissionBoard {
    public:
        std::string mission_index_char[6] = {"Current_Length","Apple","Bomb","Gateway","Strawberry","Melon"};

        MissionBoard(); // 기본 생성자
        void init();
        void drawBorder();
        void drawCurrent_mission(int Current_Length); // Current_Length
        void drawScore(int Score); // Score
        void drawApple_mission(int Apple); //  Apple
        void drawBomb_mission(int Bomb); //  Bomb
        void drawGateway_mission(int Gateway); // Gateway
        void drawStrawberry_mission(int Strawberry); // Strawberry
        void drawMelon_mission(int Melon); // Melon 구현시 추가
        void drawMongu_mission(int y, int mission, int goal, int mission_index); // mission_index= 특정 미션항목을 식벽하기 위한 파라미터
        void close();
        

    private:
        int height, width, start_y, start_x, goal;
        int Apple,Bomb,Gateway;
        Board board;

        WINDOW *win;
};}

#endif /* MISSIONBOARD_HPP */
