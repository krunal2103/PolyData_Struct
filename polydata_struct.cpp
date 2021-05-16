#include "polydata_struct.h"

PolyDataStruct &PolyDataStruct::operator=(const PolyDataStruct &_other) {
  clear();
  clear_functions_ = _other.clear_functions_;
  copy_functions_ = _other.copy_functions_;

  for (auto &&copy_function : copy_functions_) {
    copy_function(_other, *this);
  }
  return *this;
}

any_type PolyDataStruct::at(int index) {
  visit(index_visitor{}, index);
  auto temp = std::any_cast<any_type>(item_);
  item_.reset();
  return temp;
}

int PolyDataStruct::length() const { return size_; }

bool PolyDataStruct::empty() const { return size_ == 0; }

void PolyDataStruct::display() {
  for (int i = 0; i < size_; i++) {
    any_type val = at(i);
    std::visit([](auto &&arg) { std::cout << arg << " "; }, val);
  }
  std::cout << std::endl;
}

void PolyDataStruct::clear() {
  for (auto &&clear_func : clear_functions_) {
    clear_func(*this);
  }
}
