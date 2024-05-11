#if defined(__MINGW32__)
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

int main() { 
    initscr();
    printw("Hello World!!!");
    refresh();
    getch();
    endwin();
    return 0;
}