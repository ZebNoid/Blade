#pragma once

#include <stdexcept>
#include <string>

namespace Blade::Tests {

inline auto ExpectEqual(int actual, int expected, const char* name) -> void
{
    if (actual == expected) return;
    throw std::runtime_error(std::string(name) + ": expected " + std::to_string(expected) + ", actual " + std::to_string(actual));
}

} // namespace Blade::Tests
