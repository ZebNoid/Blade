#pragma once

#include <string>

namespace Blade::Api {

struct Point
{
    int x{};
    int y{};
};

inline auto to_string(const Point& point) -> std::wstring
{
    return L"[" +
        std::to_wstring(point.x) +
        L" x " +
        std::to_wstring(point.y) +
        L"]";
}

} // namespace Blade::Api
