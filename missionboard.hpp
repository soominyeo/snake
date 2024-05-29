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
        /*bool mission_Current_Length = false, mission_Apple = false, 
        mission_Bomb = false, mission_Gateway = false;*/
        
        std::string mission_index_char[4] = {"Current_Length","Apple","Bomb","Gateway"};

        MissionBoard(); // 기본 생성자
        void init();
        void drawBorder();
        void drawCurrent_mission(int Current_Length); // Current_Length
        void drawApple_mission(int Apple); //  Apple
        void drawBomb_mission(int Bomb); //  Bomb
        void drawGateway_mission(int Gateway); // Gateway
        void drawMongu_mission(int y, int mission, int goal, int mission_index); // mission_index= 특정 미션항목을 식벽하기 위한 파라미터
        void close();
        

    private:
        int height, width, start_y, start_x, goal;
        int Apple,Bomb,Gateway;
        Board board;

        WINDOW *win;
};}

#endif /* MISSIONBOARD_HPP */
