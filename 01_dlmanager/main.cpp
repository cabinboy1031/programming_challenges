#include "main.h"
// I want to use curses to show download progress
// Downloads should be managed with priorities, limits, and importantly, sources and destinations

int main(){
  /*initialise curses  */
  initscr();
  cbreak();
  noecho();

  mvprintw(10,5,"Hello world");

  getch();
  //cleanup
  clear();
  refresh();
  endwin();

  exit(0);
  return 0;
}
