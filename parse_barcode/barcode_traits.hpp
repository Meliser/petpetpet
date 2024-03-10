#pragma once

enum class BarcodeType
{
    typeA,
    typeB,
    typeC,
    typeCExt,
    _unknown
};

struct UnknownBarcode;

template <typename BarcodeT>
struct barcode_traits_impl
{
    using type = BarcodeT;
};

template <typename BarcodeT>
struct barcode_traits;

template<>
struct barcode_traits<UnknownBarcode> : barcode_traits_impl<UnknownBarcode>
{
    static constexpr BarcodeType type_enum = BarcodeType::_unknown;
};

template <typename Barcode, typename...Barcodes>
struct BarcodesList
{
    static BarcodeType get_type(const std::string& raw)
    {
        if (barcode_traits<Barcode>::check(raw))
            return barcode_traits<Barcode>::type_enum;
        else
            return BarcodesList<Barcodes...>::get_type(raw);
    }
};

template <typename Barcode>
struct BarcodesList<Barcode>
{
    static BarcodeType get_type(const std::string& raw)
    {
        if (barcode_traits<Barcode>::check(raw))
            return barcode_traits<Barcode>::type_enum;
        else
            return barcode_traits<UnknownBarcode>::type_enum;
    }
};

template <typename T, typename U>
T barcode_cast(U src)
{
    return barcode_traits<T>::cast(src);
}