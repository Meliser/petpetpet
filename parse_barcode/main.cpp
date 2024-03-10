
#include <cassert>
#include <string>
#include <iostream>

#include "a.hpp"
#include "b.hpp"
#include "c.hpp"


BarcodeType get_type_from_all(const std::string& raw) {
    return BarcodesList<A, B, C, CExt>::get_type(raw);
}

BarcodeType get_type_from_c_only(const std::string& raw) {
    return BarcodesList<C, CExt>::get_type(raw);
}

int main()
{
    {
        std::string bc = "AFF12A14B154";
        assert(BarcodeType::typeA == get_type_from_all(bc));
        A a_bc = barcode_cast<A>(bc);
        assert(BarcodeType::_unknown == get_type_from_c_only(bc));
    }

    {
        std::string bc = "BFF12A14B154";
        assert(BarcodeType::typeB == get_type_from_all(bc));
        A a_bc = barcode_cast<A>(bc);
        B b_bc = barcode_cast<B>(bc);
        B ab_bc = barcode_cast<B>(a_bc);
    }

    {
        std::string bc = "C1234567890";
        assert(BarcodeType::typeC == get_type_from_c_only(bc));
        CExt cext_bc = barcode_cast<CExt>(bc);
    }
}