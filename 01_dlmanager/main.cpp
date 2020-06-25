#include "main.hpp"
// I want to use curses to show download progress
// Downloads should be managed with priorities, limits, and importantly, sources and destinations

int main(){
  /*initialise curses  */
  initscr();
  cbreak();
  noecho();

  refresh();
  WINDOW* test_win(newwin(LINES-3,COLS-3,2,2));
  link test(link("~/Downloads"));
  test.set_name("testfile.txt");
  test.set_priority(10);
  wprintw(test_win, "\n");
  for(int i=0;i<20;i++){
    wprintw(test_win," %s | [%%%d]\n %s | Priority: %d\n ~~~~~~~~~~~~~~\n",
            test.get_name(),
            20,
            test.get_destination(),
            test.get_priority());
    box(test_win, 0,0);
    wrefresh(test_win);
  }

  getch();
  //cleanup
  clear();
  refresh();
  delwin(test_win);
  endwin();

  exit(0);
  return 0;
}
