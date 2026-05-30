#pragma once

#include <functional>
#include <string_view>

namespace Blade::Tests {

class TestRunner
{
public:
    auto Run(std::string_view name, const std::function<void()>& test) -> void;
    auto Result() const -> int;

private:
    int m_passed = 0;
    int m_failed = 0;
};

} // namespace Blade::Tests
