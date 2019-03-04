#ifndef _POLYDATASTRUCT_H_
#define _POLYDATASTRUCT_H_

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
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
    // constructor
    PolyDataStruct():size(0) {};

    // copy constructor
    PolyDataStruct(const PolyDataStruct& _other)
    {
       *this = _other;
    }

    // Assignment operator for object
    // Example:
    // PolyDataStruct a;
    // PolyDataStruct b = a;
    PolyDataStruct& operator=(const PolyDataStruct& _other);

    // Function to push data to the object similar to a vector
    template<class T>
    void push_back(const T& _t);

    // Clear the object
    void clear();

    // Function to tell number of elements belonging to a particular data type
    // template<class T>
    // size_t number_of() const;

    // template<class T>
    // std::vector<T> get() const;

    // size_t size() const;

    // Visits every data point in the object and performs the passed operation on it
    template<class T>
    void visit(T&& visitor);

    // template<class T>
    // int length() const;

    // Destructor
    ~PolyDataStruct()
    {
        clear();
    }

    private:
    // template<class T>
    // static std::map<const PolyDataStruct*, std::vector<T>> items;

    int size;

    template<class T>
    static std::map<const PolyDataStruct*, std::map<int, T>> items;

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
    // std::vector<std::function<size_t(const PolyDataStruct&)>> size_functions;

};

template<class T>
std::map<const PolyDataStruct*, std::map<int, T>> PolyDataStruct::items;

struct print_visitor : visitor_base<int, double, char, std::string>
{
    template<class T>
    void operator()(T& _in)
    {
        std::cout << _in.first << " " << _in.second << std::endl;
    }
};

#include "polydata_struct_impl.h"
#endif
