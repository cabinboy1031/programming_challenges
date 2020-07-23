/*
  Challenge 10: Todo list application on CLI.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "functions.h"
#include "item.h"

int main(int argc, char** argv){
  std::vector<Item> todoList;
  
	std::string command;
  std::cout << "Insert a command (H for help)" << std::endl << "> ";
  do{
		getline(std::cin, command);
    switch (command[0]){
    case 'a':
      add_item(todoList);
      break;
    case 'd':
      delete_item(todoList);
      break;
    case 't':
      print_days(todoList,0,0);
      break;
    }
    std::cout << "Insert a command (H for help)" << std::endl << "> ";
  } while(command != "q");
}
std::vector<std::string> get_list(std::string filepath){
  std::ifstream stream;
  std::vector<std::string> list;
  std::string buffer;
  
  stream.open(filepath);
  while(!stream.eof()){
    stream >> buffer;
    list.push_back(buffer);
  }
  
  return list;
}

void save_list(std::vector<Item> list, std::string filepath){
  
}
void add_item(std::vector<Item> &list){
  std::string title;
  std::string description;
  std::cout << "Title: ";
	std::getline(std::cin,title);
  if(title.empty()){
    std::cerr << "No title given." << std::endl;
		return;
  }
  std::cout << "Description: ";
	getline(std::cin,description);
  if(description.empty()){
    std::cerr << "No description given." << std::endl;
  }
  list.push_back(Item(title,description));
  std::cout << "List written successfully." << std::endl;
}

void delete_item(std::vector<Item> &list){
  
}
void print_days(const std::vector<Item> &list, int start, int end){
  for(Item item : list){
    std::cout << "Title:" << item._title << std::endl;
    std::cout << "Desc:" << item._description << std::endl;
  }
}	
