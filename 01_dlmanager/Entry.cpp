#include "Entry.hpp"
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
