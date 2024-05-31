#include "missionboard.hpp"

namespace snake {

MissionBoard::MissionBoard() :
    height(17), width(50), start_y(1), start_x(1), goal(5) {}

void MissionBoard::init() {
    // ncurses 초기화
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);

    // 터미널 크기 가져오기
    int term_height, term_width;
    getmaxyx(stdscr, term_height, term_width);

    // 기본초기화 값 세팅
    Apple = 0; Bomb = 0; Gateway = 0;

    // 보드 위치 계산
    start_x = term_width - width;

    // 새로운 윈도우 생성
    win = newwin(height, width, start_y, start_x);
    refresh();

    // 색 초기화
    if (has_colors()) {
        start_color();
        // 색상 쌍 정의: 쌍 번호, 미션 완료 색, 배경 색
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
    }

    // draw methods 호출
    drawBorder();
    drawScore(0);
    drawCurrent_mission(0); // 초기 값 0으로 설정
    drawApple_mission(0); // 초기 값 0으로 설정
    drawBomb_mission(0); // 초기 값 0으로 설정
    drawGateway_mission(0); // 초기 값 0으로 설정
    drawStrawberry_mission(0); // 초기 값 0으로 설정
    // drawMelon_mission(0); // 초기 값 0으로 설정
}

void MissionBoard::drawBorder() {
    // 보더 그리기
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(win, 0, 1, " Mission Board ");
    wrefresh(win);
}
void MissionBoard::drawScore(int Score) {
    mvwprintw(win, start_y + 13, 20, "Score: %d", Score);
    wrefresh(win);
}

void MissionBoard::drawCurrent_mission(int Current_Length) {
    int mission_y = start_y + 1;
    int mission_index = 0;
    drawMongu_mission(mission_y, Current_Length, goal, mission_index);
}

void MissionBoard::drawApple_mission(int Apple) {
    int mission_y = start_y + 3;
    int mission_index = 1;
    drawMongu_mission(mission_y, Apple, goal, mission_index);
}

void MissionBoard::drawBomb_mission(int Bomb) {
    int mission_y = start_y + 5;
    int mission_index = 2;
    drawMongu_mission(mission_y, Bomb, goal, mission_index);
}

void MissionBoard::drawGateway_mission(int Gateway) {
    int mission_y = start_y + 7;
    int mission_index = 3;
    drawMongu_mission(mission_y, Gateway, goal, mission_index);
}

void MissionBoard::drawStrawberry_mission(int Strawberry) {
    int mission_y = start_y + 9;
    int mission_index = 4;
    drawMongu_mission(mission_y, Strawberry, goal, mission_index);
}
void MissionBoard::drawMelon_mission(int Melon) {
    int mission_y = start_y + 11;
    int mission_index = 5;
    drawMongu_mission(mission_y, Melon, goal, mission_index);
}

void MissionBoard::drawMongu_mission(int y, int mission, int goal, int mission_index) {
    int mission_check_x = 1;
    bool mission_completed = (mission >= goal);

    if (mission_completed) {
        wattron(win, COLOR_PAIR(1));
    }

    if (mission < goal) {
        mvwprintw(win, y, mission_check_x, "[   ]");
    } else {
        mvwprintw(win, y, mission_check_x, "[ V ]");
    }

    mission_check_x += 5; // fix_value

    mvwprintw(win, y, mission_check_x, "%s", mission_index_char[mission_index].c_str());

    int goal_x = mission_check_x + mission_index_char[mission_index].length();
    mvwprintw(win, y, goal_x, "(%d / %d)", mission, goal);

    if (mission_completed) {
        wattroff(win, COLOR_PAIR(1));
    }

    wrefresh(win);
}

void MissionBoard::close() {
    delwin(win);
    endwin();
}

} // namespace snake
