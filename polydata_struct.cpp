#include "polydata_struct.h"

PolyDataStruct& PolyDataStruct::operator=(const PolyDataStruct& _other)
{
    clear();
    clear_functions = _other.clear_functions;
    copy_functions = _other.copy_functions;

    for (auto&& copy_function : copy_functions)
    {
        copy_function(_other, *this);
    }
    return *this;
}

any_type PolyDataStruct::at(int index){
    visit(index_visitor{}, index);
    auto temp = std::any_cast<any_type>(item);
    item.reset();
    return temp;
}


int PolyDataStruct::length() const
{
  return size;
}

bool PolyDataStruct::empty() const
{
    return size == 0;
}

void PolyDataStruct::display()
{
  for(int i = 0; i < size; i++){
    any_type val = at(i);
    std::visit([](auto&& arg) {
        std::cout << arg << " ";
    }, val);
  }
  std::cout << std::endl;
}

void PolyDataStruct::clear()
{
    for (auto&& clear_func : clear_functions)
    {
        clear_func(*this);
    }
}
