#pragma once
#include "barcode_traits.hpp"
#include <string>

// ШК типа А
struct A
{
    int a;
    double b;
    char c;
};

template<>
struct barcode_traits<A> : barcode_traits_impl<A>
{
    static constexpr BarcodeType type_enum = BarcodeType::typeA;
    static A cast(const std::string& raw) {
        A a;
        a.a = 3;
        a.b = 12.421;
        a.c = '2';
        return a;
    }
    static bool check(const std::string& raw) {
        if (raw[0] == 'A')
            return true;
        else
            return false;
    }
};