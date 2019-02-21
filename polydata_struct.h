#ifndef _POLYDATASTRUCT_H_
#define _POLYDATASTRUCT_H_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <experimental/type_traits>


template<class...>
struct type_list{};

template<class... TYPES>
struct visitor_base
{
    using types = type_list<TYPES...>;
};


struct PolyDataStruct
{
    public:
    PolyDataStruct() = default;
    PolyDataStruct(const PolyDataStruct& _other)
    {
       *this = _other;
    }

    PolyDataStruct& operator=(const PolyDataStruct& _other);

    template<class T>
    void push_back(const T& _t);

    void clear();

    template<class T>
    size_t number_of() const;

    size_t size() const;

    template<class T>
    void visit(T&& visitor);

    ~PolyDataStruct()
    {
        clear();
    }

    private:
    template<class T>
    static std::unordered_map<const PolyDataStruct*, std::vector<T>> items;

    template<class T, class U>
    using visit_function = decltype(std::declval<T>().operator()(std::declval<U&>()));
    template<class T, class U>
    static constexpr bool has_visit_v = std::experimental::is_detected<visit_function, T, U>::value;

    template<class T, template<class...> class TLIST, class... TYPES>
    void visit_impl(T&& visitor, TLIST<TYPES...>);

    template<class T, class U>
    void visit_impl_help(T& visitor);

    std::vector<std::function<void(PolyDataStruct&)>> clear_functions;
    std::vector<std::function<void(const PolyDataStruct&, PolyDataStruct&)>> copy_functions;
    std::vector<std::function<size_t(const PolyDataStruct&)>> size_functions;

};

template<class T>
std::unordered_map<const PolyDataStruct*, std::vector<T>> PolyDataStruct::items;

struct print_visitor : visitor_base<int, double, char, std::string>
{
    template<class T>
    void operator()(T& _in)
    {
        std::cout << _in << " ";
    }
};

struct my_visitor : visitor_base<int, double>
{
    template<class T>
    void operator()(T& _in)
    {
        _in +=_in;
    }
};

#include "polydata_struct_impl.h"
#endif
