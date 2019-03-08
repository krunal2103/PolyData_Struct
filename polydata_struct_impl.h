template<class T>
void PolyDataStruct::push_back(const T& _t)
{
    // don't have it yet, so create functions for copying and destroying
    if (items<T>.find(this) == std::end(items<T>))
    {
        clear_functions.emplace_back([](PolyDataStruct& _c){items<T>.erase(&_c);});

        // if someone copies me, they need to call each copy_function and pass themself
        copy_functions.emplace_back([](const PolyDataStruct& _from, PolyDataStruct& _to)
        {
            items<T>[&_to] = items<T>[&_from];
        });
    }
    items<T>[this].insert(std::pair<int, T>(size, _t));
    size++;
}

template<class T>
void PolyDataStruct::visit(T&& visitor, int index)
{
    visit_impl(visitor, index, typename std::decay_t<T>::types{});
}

template<class T>
size_t PolyDataStruct::number_of() const
{
    auto iter = items<T>.find(this);
    if (iter != items<T>.cend())
        return items<T>[this].size();
    return 0;
}


template<class T>
T PolyDataStruct::get(int index) {
    T result{0};
    any_type val = at(index);
    try {
      result = std::get<T>(val);
    }
    catch (std::bad_variant_access&) {
      std::cout << "Expected type of element is different from the type of element present in the container!\n";
    }
    return result;
}

template<class T, template<class...> class TLIST, class... TYPES>
void PolyDataStruct::visit_impl(T&& visitor, int index, TLIST<TYPES...>)
{
    (..., visit_impl_help<std::decay_t<T>, TYPES>(visitor, index));
}

template<class T, class U>
void PolyDataStruct::visit_impl_help(T& visitor, int index)
{
    // static_assert(has_visit_v<T, U>, "Visitors must provide a visit function accepting a reference for each type");
    for (auto&& element : items<U>[this])
    {
        any_type val = visitor(element, index);
        if(std::holds_alternative<std::string>(val)){
            if(std::get<std::string>(val) == "NULL"){
              continue;
            }
        }else{
            item = val;
            break;
        }
    }
}
