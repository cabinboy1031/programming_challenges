#include <iostream>
#include <string>

struct Input{
  float value;
  float weight;
};

class Node{
public:
  Node();
  ~Node();
private:
  Input* list;
  float weights;
  Input output;
  Node** next;
};

int main(){
}
