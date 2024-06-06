#include <iostream>
#include <fstream>
#include <sstream>
#include "leaderboard.hpp"

namespace snake {
    const std::string LeaderBoard::rankingFile = "ranking";
    const int LeaderBoard::rankRange = 15;
    const char LeaderBoard::delimiter = ',';

    LeaderBoard::LeaderBoard() : height(rankRange+4), width(75), start_y(0), start_x(0) {};

    void LeaderBoard::init() {
        load();

        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    }

    void LeaderBoard::show() {
        win = newwin(height, width, start_y, start_x);
        refresh();
        
        drawBorder();
        drawHeader();
        int i=0;
        for(auto it=ranking.begin(); it!=ranking.end(); it++) {
            drawScore(i++, it->name, it->score);
        }
        wrefresh(win);
    }

    void LeaderBoard::drawBorder() {
        box(win, 0, 0);
    }


    void LeaderBoard::drawHeader() {
        mvwprintw(win, start_y+1, start_x+1, "rank\t %10s\t %s", "name", "score");
    }

    void LeaderBoard::drawScore(int idx, std::string name, int score) {
        mvwprintw(win, start_y+3+idx, start_x+1, "%2d\t %10s\t %d", idx+1, name.c_str(), score);
    }

    void LeaderBoard::close() {
        delwin(win);
        endwin();
    }

    void LeaderBoard::addRank(Rank rank) {
        ranking.insert(rank);
        
        while (ranking.size() > rankRange) {
            ranking.erase(std::prev(ranking.end()));
        }
    }

    void LeaderBoard::clearRank() {
        ranking.clear();
    }

    void LeaderBoard::load() {
        std::ofstream dfs("debug", std::ios_base::out | std::ios_base::app);

        std::ifstream ifs(rankingFile, std::ios_base::in);
        std::stringstream ss;
        std::string line;

        std::string name;
        int score;
        while (std::getline(ifs, line)) {
            ss << line;
            std::getline(ss, name, delimiter);
            ss >> score;
            std::stringstream().swap(ss);

            addRank(Rank(name, score));
            dfs << "loaded " << name << "(" << score << ")" << std::endl;
        }
        ifs.close();
        dfs.close();
    }

    void LeaderBoard::save() {
        std::ofstream dfs("debug", std::ios_base::out | std::ios_base::app);

        std::ofstream ofs(rankingFile, std::ios_base::out);
        for(auto it=ranking.begin(); it!=ranking.end(); it++) {
            ofs << it->name << delimiter << it->score << std::endl;
            dfs << "saved " << it->name << "(" << it->score << ")" << std::endl;
        }
        ofs.close();
        dfs.close();
    }


    Rank::Rank(std::string n, int s) : name(n), score(s) {};

    bool Rank::operator<(const Rank& rhs) const {
        return (score != rhs.score) ? (score > rhs.score) : (name > rhs.name);
    }
}