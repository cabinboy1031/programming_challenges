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
			case 's':
				// save_list();
			case 'l':
				// load_list();
			case 'h':
				std::cout << "Help:" << std::endl
				  << "a: Add item to a list" << std::endl
					<< "d: Delete an item from the list" << std::endl
					<< "t: Print the current todo list" << std::endl
					<< "h: display this screen" << std::endl
					<< "q: quit the program" << std::endl << std::endl
					<< "No matter what you write down, the first character of the given input is the only one that is processed." << std::endl;
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
	std::cout << "Please enter the number of the item you want to remove." << std::endl;
	for(int i = 0; i < list.size();i++){
		std::cout << i << ") " << list[i]._title << std::endl;
	}
	std::string to_remove;
	getline(std::cin, to_remove);
	int remove_pos = stoi(to_remove);
	if(remove_pos >= list.size()){
		std::cout << "Invalid entry." << std::endl;
	} else {
		list.erase(list.begin() + remove_pos);
	}
  
}
void print_days(const std::vector<Item> &list, int start, int end){
  for(Item item : list){
    std::cout << "Title:" << item._title << std::endl;
    std::cout << "Desc:" << item._description << std::endl;
  }
}	
