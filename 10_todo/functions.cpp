#include "functions.h"

using json = nlohmann::json;

void save_list(std::vector<Item> list, std::string filepath){
	json list_json = json::array();

	for(int i = 0; i < list.size(); i++){
		list_json[i] = json(
				{
				{"title", list[i]._title},
				{"description", list[i]._description}
				}
				);
	}

	//save in given file;
	std::ofstream file;
	file.open(filepath, std::ofstream::out | std::ofstream::trunc);

	if(!file.is_open()){
		std::cerr << "Error saving file! Unable to access filepath!" << std::endl;
	} else {
		file << list_json.dump(2);
	}

	//cleanup and ensure the file is closed
	file.close();
}

std::vector<Item> load_list(std::string filepath){
	std::vector<Item> buf_list;

	// load from filepath first
	std::ifstream file;
	file.open(filepath);
	if(!file.is_open()){
		std::cerr << "Error loading file! Does it exist?" << std::endl;
		return buf_list;
	}
	
	// Load into JSON object
	json input_json;
	file >> input_json;
	file.close();

	// Add to buffer list
	Item buf_item;
	for(int i = 0; i < input_json.size(); i++){
		buf_item._title = input_json[i]["title"];
		buf_item._description = input_json[i]["description"];
		buf_list.push_back(buf_item);
	}	

	print_days(buf_list, 0,0);
	return buf_list;
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
