#pragma once

class Scoreboard
{
    WINDOW *score_win;
public:
    Scoreboard();
    Scoreboard(int width, int y, int x);

    void initialize(int initial_score);
    void updateScore(int score);
    void clear();
    void refresh();
};