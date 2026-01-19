#include <codecvt>
#include <locale>
#include "../include/string_utils.hpp"

//string -> wstring
std::wstring toWString(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}

// wstring -> string
std::string toString(const std::wstring& ws) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(ws);
}