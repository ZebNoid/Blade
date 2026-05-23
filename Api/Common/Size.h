#pragma once
#include <string>

namespace Blade::Api {

struct Size
{
    int width{};
    int height{};
};

inline auto to_string(const Size& size) -> std::wstring
{
    return L"[" +
        std::to_wstring(size.width) +
        L" x " +
        std::to_wstring(size.height) +
        L"]";
}

} // namespace
