#pragma once

#include "barcode_traits.hpp"
#include <stdexcept>
#include <string>

// ШК типа С
struct C
{
    std::string name;
    std::string surname;
    int year;
};

// ШК типа С расширенный (расширение С)
struct CExt : C
{
    int month;
    int day;
};

template<>
struct barcode_traits<C> : barcode_traits_impl<C>
{
    static constexpr BarcodeType type_enum = BarcodeType::typeC;
    static C cast(const std::string& raw) {
        if (!check(raw))
            throw std::runtime_error {"Failed to cast to C format. Mask mismatch"};
        C a;
        a.name = "Hello";
        a.surname = "Master";
        return a;
    }
    static bool check(const std::string& raw) {
        if (raw[0] == 'C' && raw.length() > 5)
            return true;
        else
            return false;
    }
};

template<>
struct barcode_traits<CExt> : barcode_traits_impl<CExt>
{
    static constexpr BarcodeType type_enum = BarcodeType::typeCExt;
    static CExt cast(const std::string& raw) {
        if (!check(raw))
            throw std::runtime_error {"Failed to cast to CExt format. Mask mismatch"};
        CExt ext {barcode_traits<C>::cast(raw)};
        ext.day = 12;
        ext.month = 2;
        return ext;
    }
    static bool check(const std::string& raw) {
        if (raw[0] == 'C' && raw.length() > 10)
            return true;
        else
            return false;
    }
};