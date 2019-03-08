#include "polydata_struct.h"
#include <map>

int main(){
  // auto print_container = [](PolyDataStruct& _in){_in.visit(print_visitor{}); std::cout << std::endl;};
  PolyDataStruct c;
  c.push_back('a');
  c.push_back(10);
  c.push_back(1.25);
  c.push_back(12345);
  for(int i = 0; i < 4; i++){
    any_type val = c.at(i);
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>)
            std::cout << "int with value " << arg << '\n';
        else if constexpr (std::is_same_v<T, float>)
            std::cout << "float with value " << arg << '\n';
        else if constexpr (std::is_same_v<T, long>)
            std::cout << "long with value " << arg << '\n';
        else if constexpr (std::is_same_v<T, double>)
            std::cout << "double with value " << arg << '\n';
        else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "std::string with value " << arg << '\n';
        else if constexpr (std::is_same_v<T, char>)
            std::cout << "char with value " << arg << '\n';
        else
            std::cout << "non-exhaustive visitor!\n";
    }, val);
  }
  return 0;
}
