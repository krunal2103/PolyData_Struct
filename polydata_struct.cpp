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
    any_type temp = std::any_cast<any_type>(item);
    item.reset();
    return temp;
}


int PolyDataStruct::length() const
{
  return size;
}

void PolyDataStruct::clear()
{
    for (auto&& clear_func : clear_functions)
    {
        clear_func(*this);
    }
}

// size_t PolyDataStruct::size() const
// {
//     size_t sum = 0;
//     for (auto&& size_func : size_functions)
//     {
//         sum += size_func(*this);
//     }
//     // gotta be careful about this overflowing
//     return sum;
// }
