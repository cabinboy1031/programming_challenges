#ifndef item_h_INCLUDED
#define item_h_INCLUDED
#include <iostream>
#include <string>

struct Item{
  std::string _title;
  std::string _description;

  Item(std::string = "", std::string = "");
};

#endif // item_h_INCLUDED
