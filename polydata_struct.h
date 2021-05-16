#ifndef _POLYDATASTRUCT_H_
#define _POLYDATASTRUCT_H_

#include <any>
#include <type_traits>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using any_type = std::variant<int, float, double, std::string, char>;

template <class...> struct type_list {};

template <class... TYPES> struct visitor_base {
  using types = type_list<TYPES...>;
};

struct PolyDataStruct {
private:
  struct proxy {
    proxy(PolyDataStruct *polyDataStruct, int i)
        : polyDataStruct(polyDataStruct), i(i) {}
    PolyDataStruct *polyDataStruct;
    int i;

    template <typename T> operator T() { return polyDataStruct->get<T>(i); }
  };

public:
  // constructor
  PolyDataStruct() : size_(0){};

  // copy constructor
  PolyDataStruct(const PolyDataStruct &_other) { *this = _other; }

  // Assignment operator for object
  // Example:
  // PolyDataStruct a;
  // PolyDataStruct b = a;
  PolyDataStruct &operator=(const PolyDataStruct &_other);

  // Function to push data to the object similar to a vector
  template <class T> void push_back(const T &_t);

  // Clear the object
  void clear();

  // Function to tell number of elements belonging to a particular data type
  template <class T> size_t number_of() const;

  template <class T> T get(int index);

  proxy operator[](int index) { return proxy(this, index); }

  bool empty() const;

  void display();

  // Visits every data point in the object and performs the passed operation on
  // it
  template <class T> void visit(T &&visitor, int index = -1);

  any_type at(int index);

  int length() const;

  template <class T> void set_item(T v);

  // Destructor
  ~PolyDataStruct() { clear(); }

private:
  template <class T, template <class...> class TLIST, class... TYPES>
  void visit_impl(T &&visitor, int index, TLIST<TYPES...>);

  template <class T, class U> void visit_impl_help(T &visitor, int index);


  int size_{};

  std::any item_;

  template <class T>
  static std::unordered_map<const PolyDataStruct *, std::unordered_map<int, T>>
      items_;

  std::vector<std::function<void(PolyDataStruct &)>> clear_functions_;
  std::vector<std::function<void(const PolyDataStruct &, PolyDataStruct &)>>
      copy_functions_;
};

template <class T>
std::unordered_map<const PolyDataStruct *, std::unordered_map<int, T>> PolyDataStruct::items_;

struct index_visitor : visitor_base<int, float, double, char, std::string> {
  template <class T> any_type operator()(T &_in, int index) {
    if (_in.first == index && index >= 0) {
      return _in.second;
    } else {
      return "NULL";
    }
  }
};

#include "polydata_struct_impl.h"
#endif
