#pragma once

#include "a.hpp"
#include "barcode_traits.hpp"
#include <string>

// ШК типа Б
struct B
{
    int x;
    int y;
    int z;
};

template<>
struct barcode_traits<B> : barcode_traits_impl<B>
{
    static constexpr BarcodeType type_enum = BarcodeType::typeB;
    static B cast(const std::string& raw) {
        B b;
        b.x = 3;
        b.y = 5;
        b.z = 65;
        return b;
    }
    static B cast(const A& bc) {
        B b;
        b.x = 10;
        b.y = 12;
        b.z = 563;
        return b;
    }
    static bool check(const std::string& raw) {
        if (raw[0] == 'B')
            return true;
        else
            return false;
    }
};
