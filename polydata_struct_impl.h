template <class T> void PolyDataStruct::push_back(const T &_t) {
  // don't have it yet, so create functions for copying and destroying
  if (items_<T>.find(this) == std::end(items_<T>)) {
    clear_functions_.emplace_back(
        [](PolyDataStruct &_c) { items_<T>.erase(&_c); });

    // if someone copies me, they need to call each copy_function and pass
    // themself
    copy_functions_.emplace_back(
        [](const PolyDataStruct &_from, PolyDataStruct &_to) {
          items_<T>[&_to] = items_<T>[&_from];
        });
  }
  items_<T>[this].insert(std::pair<int, T>(size_, _t));
  size_++;
}

template <class T> void PolyDataStruct::visit(T &&visitor, int index) {
  visit_impl(visitor, index, typename std::decay_t<T>::types{});
}

template <class T> size_t PolyDataStruct::number_of() const {
  auto iter = items_<T>.find(this);
  if (iter != items_<T>.cend())
    return items_<T>.at(this).size();
  else
    return 0;
}

template <class T> T PolyDataStruct::get(int index) {
  T result{0};
  any_type val = at(index);
  try {
    result = std::get<T>(val);
  } catch (std::bad_variant_access &) {
    std::cerr << "Expected type of element is different from the type of "
                 "element present in the container!\n";
  }
  return result;
}

template <class T> void PolyDataStruct::set_item(T v) { item_ = v; }

template <class T, template <class...> class TLIST, class... TYPES>
void PolyDataStruct::visit_impl(T &&visitor, int index, TLIST<TYPES...>) {
  (..., visit_impl_help<std::decay_t<T>, TYPES>(visitor, index));
}

template <class T, class U>
void PolyDataStruct::visit_impl_help(T &visitor, int index) {
  for (auto &&element : items_<U>[this]) {
    any_type val = visitor(element, index);
    if (std::holds_alternative<std::string>(val)) {
      if (std::get<std::string>(val) == "NULL") {
        continue;
      } else {
        set_item(val);
        break;
      }
    } else {
      set_item(val);
      break;
    }
  }
}
