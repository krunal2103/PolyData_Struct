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
    items<T>[this].push_back(_t);
}

template<class T>
void PolyDataStruct::visit(T&& visitor)
{
    visit_impl(visitor, typename std::decay_t<T>::types{});
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
std::vector<T> PolyDataStruct::get() const
{
    auto iter = items<T>.find(this);
    if (iter != items<T>.cend())
        return items<T>[this];
    return {0};
}

template<class T, template<class...> class TLIST, class... TYPES>
void PolyDataStruct::visit_impl(T&& visitor, TLIST<TYPES...>)
{
    (..., visit_impl_help<std::decay_t<T>, TYPES>(visitor));
}

template<class T, class U>
void PolyDataStruct::visit_impl_help(T& visitor)
{
    static_assert(has_visit_v<T, U>, "Visitors must provide a visit function accepting a reference for each type");
    for (auto&& element : items<U>[this])
    {
        visitor(element);
    }
}
