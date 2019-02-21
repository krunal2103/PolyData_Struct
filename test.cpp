#include "polydata_struct.h"

int main(){
  auto print_container = [](PolyDataStruct& _in){_in.visit(print_visitor{}); std::cout << std::endl;};
  PolyDataStruct c;
  c.push_back('a');
  c.push_back(10);
  c.push_back(1.25);
  print_container(c);
  c.visit(print_visitor{});
  std::cout << std::endl;
  c.clear();
  std::cout << "c after clearing c: ";
  c.visit(print_visitor{});
  std::cout << std::endl;
  return 0;
}
