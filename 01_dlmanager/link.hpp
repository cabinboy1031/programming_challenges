#ifndef LINK_H
#define LINK_H
#include <iostream>
#include <string>
#include <fstream>

class link{
public:
  link();
  link(std::string);
  link(const link &);
  link(link &&);
  link& operator=(const link &);
  link& operator=(link &&);

// Strings are returned as char* to be more readily compatible with ncurses functions
  const char* get_destination() const { return destination.c_str(); }
  const char* get_name() const { return name.c_str(); }
  int         get_priority() const { return priority; }

// std::string is used to allow both char* and std::string as well as string literals
  void set_name(std::string new_name){ name = new_name; }
  void set_destination(std::string new_destination){ destination = new_destination; }
  void set_priority(int new_priority) {priority = new_priority;}

private:
  std::string destination;
  std::string name;
  int priority = 0;
};
#endif //LINK_H
