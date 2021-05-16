#include "polydata_struct.h"

int main() {
  PolyDataStruct c;

  c.push_back(std::string("Hello"));
  c.push_back('a');
  c.push_back(10);
  c.push_back(1.25);
  c.push_back(12345);
  c.display();

  if (!c.empty()) {
    std::cout << "\nc has " << c.length() << " elements\n";

    std::cout << "Int: " << c.number_of<int>() << std::endl;
    std::cout << "Float: " << c.number_of<double>() << std::endl;
    std::cout << "Char: " << c.number_of<char>() << std::endl;
    std::cout << "Strings: " << c.number_of<std::string>() << std::endl;
  }
  std::cout << std::endl;

  int s = c[0];

  return 0;
}
