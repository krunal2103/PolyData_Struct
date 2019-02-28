#include "polydata_struct.h"
#include <map>

std::map <std::string, PolyDataStruct> data;

int main(){
  auto print_container = [](PolyDataStruct& _in){_in.visit(print_visitor{}); std::cout << std::endl;};
  PolyDataStruct c;
  c.push_back('a');
  c.push_back(10);
  c.push_back(1.25);
  c.push_back(12345);
  print_container(c);
  std::vector<int> v = c.get<int>();
  for(int i = 0; i < v.size(); i++){
    std::cout << v[i] << std::endl;
  }
  // c.visit(print_visitor{});
  // std::cout << std::endl;
  // c.clear();
  // std::cout << "c after clearing c: ";
  // c.visit(print_visitor{});
  // std::cout << std::endl;
  return 0;
}
