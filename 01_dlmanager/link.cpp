#include "link.hpp"

link::link(){
  destination = "";
  name = "";
  priority = 0;
}

link::link(std::string destination){
  this->destination = destination;
  name = "";
  priority = 0;
}

link::link(const link &in){
  destination = std::string(in.get_destination());
  name = in.get_name();
  priority = in.get_priority();
}

link::link(link &&in){
  destination = std::string(in.get_destination());
  name = in.get_name();
  priority = in.get_priority();

  in.set_destination("");
  in.set_name("");
  in.set_priority(0);
}
