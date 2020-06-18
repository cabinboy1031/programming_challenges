#include "main.h"
// I want to use curses to show download progress
// Downloads should be managed with priorities, limits, and importantly, sources and destinations

// entry structure for downloads
struct Entry{
  std::string _name; // The main filename,
  std::string _link; // the source link to download from
  std::string _filepath; // the directory the file is going to be downloaded to,
  int _priority; // should this file be downloaded before others( TODO thread implementation )
  // For downloads with the same name with the exception of a number on the end ex. PART_1 PART_2
  std::vector<Entry> _subEntries; //TODO Implement proper handling of subentries

  Entry();
  Entry(std::string, std::string, std::string, int = 0);
  Entry(const Entry &);
  Entry(Entry &&);
  ~Entry();
  Entry& operator=(const Entry &);
  Entry& operator=(Entry &&);

  const char* to_string();
};

// container structure for where to draw
struct Container{
  int ix,iy,nx,ny; // the container's top left and bottom right draw corners
  std::vector<Entry> _queue; // the download queue, 

  Container();
  void add(Entry &);
  void remove(Entry &);
  Entry& operator[](int);
};

int main(){
  /*initialise curses  */
  initscr();
  cbreak();
  noecho();
  //main part of the program

  // Draw the container

  // until the queue ends,
    // draw the name [progress bar]
    // draw the [progress%] | link
    // draw the filepath
    // draw each subentry name [progress bar]
    // increment the reference by 4 + [number of subentries]
  Container queue;
  Entry yes("name.txt", "https://fuckyou.org/name.txt", "~/Downloads/");
  Entry no("fuck.txt", "example.com", "~/Downloads/");
  queue.add(yes);
  queue.add(no);
  int offset = 0; // the scroll value, positive offset scrolls downwards
  for(size_t i = 0; i < queue._queue.size(); i++){
    mvprintw((4 * i) - offset,0, "%s", queue[i].to_string());
    mvprintw((4 * i) + 1 - offset,0, "%s", queue[i]._link.c_str());
    mvprintw((4 * i) + 2 - offset,0, "%s", queue[i]._filepath.c_str());
    mvprintw((4 * i) + 3 - offset,0, " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ");
  }


  getch();
  //cleanup
  clear();
  refresh();
  endwin();

  exit(0);
  return 0;
}

// Entry functions
Entry::Entry(){
  _name = "";
  _link = "";
  _filepath = "";
  _priority = 0;
}

Entry::Entry(std::string name, std::string link, std::string filepath, int priority){
  _name = name;
  _link = link;
  _filepath = filepath;
  _priority = priority;
}

Entry::Entry(const Entry &in){
  _name = in._name;
  _link = in._link;
  _filepath = in._filepath;
  _priority = in._priority;

  // if(in._subEntries.empty()){
  //   for(size_t i = 0; i < in._subEntries.size();i++){
  //     _subEntries[i] = in._subEntries[i];
  //   }
  // }
}

Entry::Entry(Entry &&in){
  _name = in._name;
  _link = in._link;
  _filepath = in._filepath;
  _priority = in._priority;
  in._name.clear();
  in._link.clear();
  in._filepath.clear();
  in._priority = 0;

  // if(in._subEntries.empty()){
  //   for(size_t i = 0; i < in._subEntries.size();i++){
  //     _subEntries[i] = in._subEntries[i];
  //   }
  //   in._subEntries.clear();
  // }
}

Entry::~Entry(){
}

const char* Entry::to_string(){
  return _name.c_str();
}

//Container functions
Container::Container(){
  ix = 0;
  iy = 0;
  nx = 0;
  ny = 0;
}

void Container::add(Entry &in){
  _queue.push_back(in);
}

Entry& Container::operator[](int idx){
  return _queue[idx];
}
