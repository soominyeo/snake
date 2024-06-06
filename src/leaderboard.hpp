#pragma once

#include <ncurses.h>
#include <string>
#include <set>

namespace snake {
    class Rank {
    public:
        std::string name;
        int score;

        Rank(std::string n, int s);
        bool operator<(const Rank& rhs) const;
    };

    class LeaderBoard {
    
    public:
        static const std::string rankingFile;
        static const int rankRange;
        static const char delimiter;

        LeaderBoard();

        void init();
        void show();
        void close();
        void addRank(Rank rank);
        void clearRank();
        void load();
        void save();
    private:
        const int height, width, start_y, start_x;
        std::set<snake::Rank> ranking;

        WINDOW *win;

        void drawBorder();
        void drawHeader();
        void drawScore(int idx, std::string name, int score);
    };
};