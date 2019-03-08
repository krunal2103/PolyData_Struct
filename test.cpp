#include "polydata_struct.h"
#include <map>

int main(){
  // auto print_container = [](PolyDataStruct& _in){_in.visit(print_visitor{}); std::cout << std::endl;};
  PolyDataStruct c;
  c.push_back('a');
  c.push_back(10);
  c.push_back(1.25);
  c.push_back(12345);
  c.display();
  return 0;
}
