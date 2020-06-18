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

  std::string get_destination() const { return destination; }
  std::string get_name() const { return name; }
  int         get_priority() const { return priority; }

  void set_name(std::string new_name){ name = new_name; }

private:
  std::string destination;
  std::string name;
  int priority = 0;
};
#endif //LINK_H
