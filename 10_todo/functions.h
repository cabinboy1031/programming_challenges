#ifndef functions_h_INCLUDED
#define functions_h_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "item.h"

std::vector<Item> load_list(std::string filepath);
void save_list(std::vector<Item> list, std::string filepath);

void add_item(std::vector<Item> &);
void delete_item(std::vector<Item> &);
void print_days(const std::vector<Item> &, int, int);

#endif // functions_h_INCLUDED

