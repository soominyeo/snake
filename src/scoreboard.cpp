#include <ncurses.h>
#include "scoreboard.hpp"

namespace snake {
    Scoreboard::Scoreboard() {}

    Scoreboard::Scoreboard(int width, int y, int x)
    {
        score_win = newwin(1, width, y, x);
    }

    void Scoreboard::initialize(int initial_score)
    {
        clear();
        mvwprintw(score_win, 0, 0, "Score:");
        updateScore(initial_score);
        refresh();
    }

    void Scoreboard::updateScore(int score)
    {
        int maxx=getmaxx(score_win);
        mvwprintw(score_win, 0, maxx - 10, "%11i", score);
    }

    void Scoreboard::clear()
    {
        wclear(score_win);
    }

    void Scoreboard::refresh()
    {
        wrefresh(score_win);
    }
}