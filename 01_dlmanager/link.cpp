#include "link.h"

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
  destination = in.get_destination();
  name = in.get_name();
  priority = in.get_priority();
}

link::link(link &&in){
  destination = in.get_destination();
  name = in.get_name();
  priority = in.get_priority();
}
