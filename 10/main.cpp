/*
  Challenge 10: Todo list application on CLI.
 */
#include <iostream>
#include <string>

struct Item{
  std::string title;
  std::string description;
  std::string priority;
  std::string date;
};
Item(std::string title, std::string description, std::string date, std::string priority){

}
struct TodoList{
  Item* items;
  int size;
  int capacity;
};


int main(int argc, char** argv){
  
}
