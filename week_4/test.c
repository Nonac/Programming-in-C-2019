#include <curses.h>

int main(void){

  initscr();

  box(stdscr,ACS_VLINE,ACS_HLINE);

  mvaddstr(15,2,"hello,world");

  refresh();

  getch();

  endwin();

  return 0;  

}
