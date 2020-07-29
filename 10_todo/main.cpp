/*
  Challenge 10: Todo list application on CLI.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
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
				save_list(todoList, "output_test.json");
				break;
			case 'l':
				todoList = load_list("output_test.json");
				break;
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
